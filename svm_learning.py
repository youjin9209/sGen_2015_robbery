from sklearn import svm
from sklearn.externals import joblib

def mLearning():
    db = open("db.txt", "r")
    data = []
    target = []
    while 1:
        buf = db.readline()
        if not buf or buf == '\n':
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
    joblib.dump(clf, 'learning.dat')
    db.close()

mLearning()
