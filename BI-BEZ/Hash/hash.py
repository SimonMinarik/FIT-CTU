from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
i = -1
y = [0, 0]
while y[0] != 0xAA or y[1] != 0xBB:
    i += 1
    digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
    digest.update(str(i).encode())
    y = (digest.finalize())
f = open("x", "w+")
f.write(i)
f.close()