import os, filecmp
from sys import argv
codes = {200:'success',404:'file not found',400:'error',408:'timeout'}

def compile(file,lang):
    if lang == 'java':
        class_file = file[:-4]+"class"
    elif lang == 'c':
        class_file = file[:-2]
    elif lang=='cpp':
        class_file = file[:-4]

    if (os.path.isfile(class_file)):
        os.remove(class_file)
    if (os.path.isfile(file)):
        if lang == 'java':
            os.system('javac '+file)
        elif lang == 'c' or lang == 'cpp':
            os.system('gcc -o '+class_file+' '+file)
        if (os.path.isfile(class_file)):
            return 200
        else:
            return 400
    else:
        return 404

def run(file,input,timeout,lang):
    if lang == 'java':
        cmd = 'java '+file
    elif lang=='c' or lang=='cpp':
        cmd = './'+file
    r = os.system('timeout '+timeout+' '+cmd+' < '+input+' > out.txt')
    if lang == 'java':
        os.remove(file+'.class')
    elif lang == 'c' or lang == 'cpp':
        os.remove(file)
    if r==0:
        return 200
    elif r==31744:
        os.remove('out.txt')
        return 408
    else:
        os.remove('out.txt')
        return 400

def match(output):
    if os.path.isfile('out.txt') and os.path.isfile(output):
        b = filecmp.cmp('out.txt',output)
        #os.remove('out.txt')
        return b
    else:
        return 404


file = raw_input('')
filename, file_extension = os.path.splittext(file);
lang = file_extension

testin = argv[1]
testout = argv[2]
timeout = '1' # secs


if lang = 'c':
	print(codes[compile(file,'c')])
	print (codes[run('add',testin,timeout,lang)])
	print (match(testout))
elif lang = 'java'
	print(codes[compile(file,'java')])
	print (codes[run('add',testin,timeout,lang)])
	print (match(testout))

