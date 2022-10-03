import cv2
import csv
import sys
import numpy as np
import tensorflow as tf
from PIL import Image as im
from tensorflow.keras.layers import Input, Lambda, Add
from tensorflow.keras.models import Model
import tensorflow.keras.backend as K

#sys.path.append('./')
import solvers.networks.base7

if __name__ == '__main__':

    SCALE=3
    IMG_COUNT=10

    print('INFO: Load: ./jpg/input.jpg')
    img = cv2.imread('./jpg/input.jpg')
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = np.expand_dims(img, axis=0) # This is to add one more dimension, batch = 1

    print('INFO: Save: ./npy/input.npy')
    np.save('./npy/input.npy', img[0])

    print('INFO: Save: ./csv/input.csv')
    f = open('csv/input.csv', 'w')
    writer = csv.writer(f)
    writer.writerow(img[0].flatten())
    f.close()

    # Load pre-trained model (.PB)
    MODEL_DIR = './model/best_status'
    model = tf.keras.models.load_model(MODEL_DIR)
    #model.summary()

    # Run model prediction
    y_keras = model.predict(img)

    print('INFO: Save: ./npy/output.npy')
    np.save('./npy/output', y_keras[0])

    print('INFO: Save: ./jpg/output.jpg')
    cv2.imwrite('./jpg/output.jpg', y_keras[0])

    print('INFO: Save: ./csv/output.csv')
    f = open('csv/output.csv', 'w')
    writer = csv.writer(f)
    writer.writerow(y_keras[0].flatten())
    f.close()


