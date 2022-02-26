import subprocess

psum = 0
case = 100

fs = open('lastscore.txt', encoding = 'utf-8', mode = 'r', newline='\n')
fscore = int(fs.readline().rstrip('\n'))
fs.close()

for i in range(case):
    textname = str(i).zfill(4) + ".txt"
    
    with open("in/"+textname) as fp:
        res = subprocess.check_output(['cargo', 'run', '--release', '--bin', 'tester', '.\h.exe'], stdin=fp, stderr=subprocess.STDOUT)
        resstr = res.decode()[res.decode().find('Score'):].rstrip('\n')[8:]
        print(f"case {str(i+1).zfill(3)} - Score:{resstr}")
        psum += int(resstr)

ps = (psum/fscore)*100

print(f"Final Score:{psum}, Highest until Last:{fscore}, Compared with Highest:{ps}%")

fs = open('lastscore.txt', encoding='utf-8', mode='w', newline='\n')
fs.write(str(max(psum, fscore)))
fs.close()