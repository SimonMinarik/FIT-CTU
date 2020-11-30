import sys
import os
import struct
import math
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend


def main(args):
    if not 1 < len(args) < 4 or args[1].upper() not in ["ENCRYPT", "DECRYPT"] or args[2].upper() not in ["ECB", "CBC"]:
        print("Wrong input, try again.\nCorrect format: file encrypt/decrypt ecb/cbc")
        exit(0)
    elif not os.access(args[0], os.R_OK):
        print("File couldn't be opened, try again.\n")
        exit(0)

    header, data = load_file(args[0])
    if args[1] == "encrypt":
        encrypted_data = crypt(data, "encrypt", args[2].upper())
        file_name = args[0][:args[0].find(".bmp")] + "_" + args[2].lower() + ".bmp"
        new_image = open(file_name, "wb")
        new_image.write(header + encrypted_data)
    else:
        decrypted_data = crypt(data, "decrypt", args[2].upper())
        file_name = args[0][:args[0].find(".bmp")] + "_" + args[2].lower() + "_dec.bmp"
        should_be_image = open(file_name, "wb")
        should_be_image.write(header + decrypted_data)


def crypt(data, type, mode):
    backend = default_backend()
    key = b'pribinacek_kakao'
    iv = b'testovaci_vektor'
    if mode == "CBC":
        mode = modes.CBC(iv)
    elif mode == "ECB":
        mode = modes.ECB()
    cipher = Cipher(algorithms.AES(key), mode, backend=backend)
    if type == "encrypt":
        cryptor = cipher.encryptor()
    elif type == "decrypt":
        cryptor = cipher.decryptor()

    new_data = cryptor.update(bytes(data)) + cryptor.finalize()
    return new_data


def load_file(path):
    image_file = open(path, "rb")
    header = image_file.read(10)
    if len(header) != 10:
        return header, b''
    tmp = image_file.read(4)
    header += tmp
    if len(tmp) != 4:
        return header, b''
    offset = struct.unpack("I", tmp)[0]
    if offset < 14:
        print("The file is corrupted")
        exit(":(")
    tmp = image_file.read(offset - 14)
    header += tmp
    if len(tmp) != offset - 14:
        return header, b''

    data = image_file.read()

    return header, data


if __name__ == '__main__':
    main(sys.argv[1:])