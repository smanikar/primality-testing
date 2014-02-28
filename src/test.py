import sys

def raw2tuples(filename):
    
    #Open the file and read all lines into list
    fid = open(filename,'r')
    fileLines = fid.readlines()
    numLines = len(fileLines)
    fid.close()

    newfile = 'mod_' + filename 
    fout = open(newfile,'w')
    
    
    #Go through each line in the file and append to list
    for lineStr in fileLines:
        lineStrArray = lineStr[:-1].split(' ')
        for i in range(0,len(lineStrArray)):
            x = lineStrArray[i] + '\n'
            fout.write(x)
        fout.write('\n')
    fout.close()

fname = sys.argv[1]
raw2tuples(fname)
