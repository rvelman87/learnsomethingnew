import re
def FindStartandEnd(S, k):
    # import pdb; pdb.set_trace()
    result = []
    if len(S) == 0 or len(k) == 0:
        return (-1,-1)
    for i  in range(0, len(S)):
        m = re.search(k, S[i:i+len(k)])
        # print("i= ", i, " " ,m)
        # if m:
        #     print(m.start())
        #     print(m.end())
        if m:
            result.append((i+m.start(), i+m.end()-1))
    if not result:
        result.append((-1, -1))
    return result


S = input("Input String             : ")
k = input("String to be searched    : ")
result = FindStartandEnd(S, k)
for i in result:
    print(i)
