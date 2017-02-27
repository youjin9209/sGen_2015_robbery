import sys
import json
import math

sys.path.append("/usr/lib/python2.7/dist-packages/sklearn")
sys.path.append("/usr/lib/python2.7/dist-packages/sklearn/externals")

from sklearn import svm
from sklearn.externals import joblib


def distance(x1, y1, x2, y2):
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
    
def arg(x1, y1, x2, y2):
    return math.atan(abs(x1-x2)/abs(y1-y2))
    
def transform(data):
    ratio_data_sub = []
    ratio =  distance(int(data[0]), int(data[1]), int(data[6]), int(data[7]))
    ratio_data_sub.append(arg(int(data[0]), int(data[1]), int(data[6]), int(data[7])))
    ratio_data_sub.append(arg(int(data[2]), int(data[3]), int(data[6]), int(data[7])))
    ratio_data_sub.append(arg(int(data[4]), int(data[5]), int(data[6]), int(data[7])))
    ratio_data_sub.append(distance(int(data[2]), int(data[3]), int(data[6]), int(data[7]))/ratio)
    ratio_data_sub.append(distance(int(data[4]), int(data[5]), int(data[6]), int(data[7]))/ratio)
    return ratio_data_sub  
    
def mPredict(data_tuple1, data_tuple2, data_tuple3):
    clf = joblib.load("learning.dat")
    ret = (int(clf.predict(data_tuple1))*int(clf.predict(data_tuple2))*int(clf.predict(data_tuple3)))
    return ret

def main():
    #mode_arg = 0 -> learning
    #mode_arg = 1 -> predicting
    #input format -> json
    js1 = json.loads(sys.argv[1])
    js2 = json.loads(sys.argv[2])
    js3 = json.loads(sys.argv[3])
    data_tuple1 = []
    data_tuple2 = []
    data_tuple3 = []
    data_tuple1.append(int(js1['head'][0]))
    data_tuple1.append(int(js1['head'][1]))
    data_tuple1.append(int(js1['left'][0]))
    data_tuple1.append(int(js1['left'][1]))
    data_tuple1.append(int(js1['right'][0]))
    data_tuple1.append(int(js1['right'][1]))
    data_tuple1.append(int(js1['center'][0]))
    data_tuple1.append(int(js1['center'][1]))
    data_tuple2.append(int(js2['head'][0]))
    data_tuple2.append(int(js2['head'][1]))
    data_tuple2.append(int(js2['left'][0]))
    data_tuple2.append(int(js2['left'][1]))
    data_tuple2.append(int(js2['right'][0]))
    data_tuple2.append(int(js2['right'][1]))
    data_tuple2.append(int(js2['center'][0]))
    data_tuple2.append(int(js2['center'][1]))
    data_tuple3.append(int(js3['head'][0]))
    data_tuple3.append(int(js3['head'][1]))
    data_tuple3.append(int(js3['left'][0]))
    data_tuple3.append(int(js3['left'][1]))
    data_tuple3.append(int(js3['right'][0]))
    data_tuple3.append(int(js3['right'][1]))
    data_tuple3.append(int(js3['center'][0]))
    data_tuple3.append(int(js3['center'][1]))
 
    return mPredict(transform(data_tuple1), transform(data_tuple2), transform(data_tuple3))

ret = main()
print ret
