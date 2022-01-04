import random
import hashlib
import requests

# 设置用户名以及姓名
appid = '20211126001010445'
appkey = '1u1OTfVQYqXPgTZLkjTC'

# 设置转换语言：自动检测-》英语
from_lang = 'auto'
to_lang = 'en'

endpoint = 'http://api.fanyi.baidu.com'
path = '/api/trans/vip/translate'
url = endpoint + path


# Generate salt and sign
# btw:salt就是个随机数，为了获得签名的
def make_md5(s, encoding='utf-8'):
    return hashlib.md5(s.encode(encoding)).hexdigest()


def translate(q):
    # random salt and get sign
    salt = random.randint(32768, 65536)
    sign = make_md5(appid + q + str(salt) + appkey)

    # Build request
    headers = {'Content-Type': 'application/x-www-form-urlencoded'}
    payload = {'appid': appid, 'q': q, 'from': from_lang, 'to': to_lang, 'salt': salt, 'sign': sign}

    # http request
    r = requests.post(url, params=payload, headers=headers)
    if r.json()['trans_result'] is None:
        return ''

    result = r.json()['trans_result']
    ret = ''
    for i in result:
        ret = ret + ' ' + i['dst']
    return ret
