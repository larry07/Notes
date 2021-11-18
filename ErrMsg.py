errMsg = """
# at[1]
# at[2]
"""

errList = errMsg.split('\n')
errRet = []
codeLineNum = []
for err in errList:
    left = err.find('[')
    right = err.rfind(']')
    if left != -1 and right != -1:
        codeLineNum.append(err[left + 1:right])  # [left,right)
    elif err != '':
        errRet.append(err)


dct = {}
filename = "foo.txt"
f = open(filename, 'r+')
line = f.readline()
while line:
    # print line,
    # print(line, end = '')# Python 3
    begin = line.find(':')
    if begin != -1 and line[:begin] in codeLineNum:
        dct[line[:begin]] = line[begin + 1:].strip('\n')
    line = f.readline()

for code in codeLineNum:
    errRet.append(dct[code])
print errRet

f.close()
