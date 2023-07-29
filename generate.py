num=109
base = "61c"
baselen = len(base)
mybase = ""
# print("O ",num)
# while(num!=0):
#     rem = (int)(num%baselen)
#     mybase = base[rem] + mybase
#     num = (num-rem)/baselen
# num = 0
# for i in range(len(mybase)):
#     if(mybase[-i-1]=='c'):
#         num += baselen**i * 2
#     elif(mybase[-i-1]=='6'):
#         num += baselen**i * 0
#     elif(mybase[-i-1]=='1'):
#         num += baselen**i * 1
# print("N ",num)
# print(mybase)
# print(len(mybase))

for i in range(100):
    num=1099511627775+i
    mybase = ""
    print("O ",num)
    while(num!=0):
        rem = (int)(num%baselen)
        mybase = base[rem] + mybase
        num = (num-rem)/baselen
    newnum = 0
    for i in range(len(mybase)):
        if(mybase[-i-1]=='c'):
            newnum += baselen**i * 2
        elif(mybase[-i-1]=='6'):
            newnum += baselen**i * 0
        elif(mybase[-i-1]=='1'):
            newnum += baselen**i * 1
    print("N ",newnum)


    print(mybase, len(mybase))
