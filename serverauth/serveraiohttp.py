#!/usr/bin/python3
import asyncio
import subprocess

import aiohttp.web_runner
from aiohttp import web
import json
import ssl
import serial
import sys
# import netifaces as ni
import os
import gostcrypto
import requests
import uuid



def serial_ports():
    import serial.tools.list_ports
    # print(serial.tools.list_ports.comports())
    result = ''
    for i in serial.tools.list_ports.comports():
        print(i.usb_info().split(" "))
        if 'VID:PID=0483:F125' in str(i.usb_info()).split(" "):
            # print(str(i.usb_info()).split(' '))
            result = str(i).split(" ")[0]
            break
    return result


routes = web.RouteTableDef()


@routes.get('/')
async def index_view(request):
    return web.Response(text='index\n')
    # return


global randstr


@routes.post('/get_randstr')
async def authentication_agent(request):
    global randstr
    data = await request.post()
    login = data.get('login')
    # filedict = dict()
    # if os.stat('users.json').st_size != 0:
    #     with open('users.json', 'r') as file:
    #         filedict.update(json.load(file))
    #         if login in filedict.keys()
    randstr = uuid.uuid4().hex
    return web.json_response(login + " " + randstr)
    # else:
    #     return web.json_response("user not found in server")


@routes.post('/reguseronserver')
async def registration_agent(request):
    data = await request.post()
    global randstr
    login = data.get('login')
    verifykey = data.get('verifykey')
    ciphertexthexed = data.get('ciphertexthexed')
    signature = data.get('signature')
    filedict = dict()
    flag = 0

    if os.stat('users.json'):
        with open('users.json', 'r') as file:
            filedict.update(json.load(file))
            cipherkeys = filedict.keys()
            for key in cipherkeys:
                cipherobj = gostcrypto.gostcipher.new(algorithm="kuznechik",
                                                      key=bytearray.fromhex(key),
                                                      mode=gostcrypto.gostcipher.MODE_ECB)
                decrypthex = cipherobj.decrypt(bytearray.fromhex(ciphertexthexed))
                decryptcounter = int(decrypthex.hex(), 16)
                if 0 <= decryptcounter <= 500:
                    filedict.get(key).update({login: [verifykey, decryptcounter]})
                    flag = 1
                    break

            if flag == 0:
                return web.json_response("This key not found on server or counter unsyncronized")

            sign_obj = gostcrypto.gostsignature.new(gostcrypto.gostsignature.MODE_256,
                                                    gostcrypto.gostsignature.CURVES_R_1323565_1_024_2019[
                                                        'id-tc26-gost-3410-2012-256-paramSetB'])
            # init hash
            hash_obj = gostcrypto.gosthash.new("streebog256", data=bytearray.fromhex(randstr))

            res = sign_obj.verify(public_key=bytearray.fromhex(verifykey),
                                  digest=bytearray.fromhex(hash_obj.hexdigest()),
                                  signature=bytearray.fromhex(signature))

            print("res=", res)
            if res:
                with open('users.json', 'w') as file_w:
                    # vk_cipherkey_counter[2]=vk_cipherkey_counter[2]+attempts
                    print(res)
                    json.dump(filedict, file_w)
                    return web.json_response(text="True")
            elif not res:
                with open('users.json', 'w') as file_w:
                    print(res)
                    json.dump(filedict, file_w)
                    return web.json_response(text="False")
    else:
        return web.json_response("file is absent in server")


@routes.post('/authbypam')
async def authentication_agent(request):
    data = await request.post()
    global randstr
    login = data.get('login')
    signature = data.get('signature')
    ciphertexthexed = data.get('ciphertexthexed')
    filedict = dict()
    flag = 0

    if os.stat('users.json'):
        with open('users.json', 'r') as file:
            filedict.update(json.load(file))
            cipherkeys = filedict.keys()
            for key in cipherkeys:
                cipherobj = gostcrypto.gostcipher.new(algorithm="kuznechik",
                                                      key=bytearray.fromhex(key),
                                                      mode=gostcrypto.gostcipher.MODE_ECB)
                decrypthex = cipherobj.decrypt(bytearray.fromhex(ciphertexthexed))
                decryptcounter = int(decrypthex.hex(), 16)
                if 0 <= decryptcounter <= 500:
                    filedict.get(key).get(login)[1] = decryptcounter
                    flag = 1
                    break

            if flag == 0:
                return web.json_response("This key not found on server or counter unsyncronized")

            sign_obj = gostcrypto.gostsignature.new(gostcrypto.gostsignature.MODE_256,
                                                    gostcrypto.gostsignature.CURVES_R_1323565_1_024_2019[
                                                        'id-tc26-gost-3410-2012-256-paramSetB'])

            # init hash
            hash_obj = gostcrypto.gosthash.new("streebog256", data=bytearray.fromhex(randstr))

            res = sign_obj.verify(public_key=bytearray.fromhex(filedict.get(key).get(login)[0]),
                                  digest=bytearray.fromhex(hash_obj.hexdigest()),
                                  signature=bytearray.fromhex(signature))
            print(res)
            if res:
                with open('users.json', 'w') as file_w:
                    json.dump(filedict, file_w)
                    return web.json_response(text="True")
            elif not res:
                with open('users.json', 'w') as file_w:
                    json.dump(filedict, file_w)
                    return web.json_response(text="False")
    else:
        return web.json_response("file is absent in server")


if __name__ == '__main__':
    print(serial_ports())
    ip_addr = '192.168.100.1'
    app = web.Application()
    app.add_routes(routes=routes)
    # ssl_context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    # ssl_context.load_cert_chain('clientcert.pem', 'clientkey.pem')
    # #
    web.run_app(app=app, host=ip_addr, port=8080, )  # ssl_context=ssl_context)
