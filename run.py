from sympy import mod_inverse
from decimal import Decimal


def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


p = 6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973340247926466653
q = 6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042159
no = 12
n = p*q
PhiN = (p-1)*(q-1)

e = 646168542467566215262707948313

print(gcd(e, PhiN))
print(' e = '+str(e))

for i in range(1, 10):
    x = 1 + i*PhiN
    if x % e == 0:
        d = int(x/e)
        break


d = mod_inverse(e, PhiN)  # inverse de e modulo phi(n)

print(' d = '+str(d))


cipherText = pow(no, e)
cipherText = cipherText % n
print(' cipher text = '+str(cipherText))

decryptedText = pow(cipherText, d)
decryptedText = decryptedText % n
print(' decrypted text = '+str(decryptedText))
