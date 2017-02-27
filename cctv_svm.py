import sys

sys.path.append("/usr/lib/python2.7/dist-packages/numpy")
sys.path.append("/usr/lib/python2.7/dist-packages/sklearn")

from sklearn import svm

def mPredict(data_tuple):
    db = open("db.txt", "r")
    data = []
    target = []
    while 1:
        buf = db.readline()
        if not buf:
            break
        if buf[-1] == "\n":
            buf = buf[:-1]
            tmp = buf.split(" ")
            data.append(tmp[0].split(","))
            target.append(int(tmp[1]))
        else:
            tmp = buf.split(" ")
            data.append(tmp[0].split(","))
            target.append(int(tmp[1]))

    # We need to calculate 'gamma' and 'C'
    # Choose the predict model
    clf = svm.SVC(gamma = 0.001, C = 100)
    clf.fit(data, target)

    ret = clf.predict(data_tuple)
    db.close()
    return ret

def main():
    #mode_arg = 0 -> learning
    #mode_arg = 1 -> predicting
    #input format -> json

    data_tuple = []
    data_tuple.append(sys.argv[1])
    data_tuple.append(sys.argv[2])
    data_tuple.append(sys.argv[3])
    data_tuple.append(sys.argv[4])
    data_tuple.append(sys.argv[5])
    data_tuple.append(sys.argv[6])
    data_tuple.append(sys.argv[7])
    data_tuple.append(sys.argv[8])

    return int(mPredict(data_tuple))

ret = main()
print ret
print sys.path
