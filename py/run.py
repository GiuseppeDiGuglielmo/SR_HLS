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
    IMG_COUNT=800

    for i in range(IMG_COUNT):
        img_id = str(i+1)
        img_id = img_id.zfill(4)

        print('INFO: Load: ./png/inputs/' + img_id + 'x3.png')
        img = cv2.imread('./png/inputs/' + img_id + 'x3.png')
        #img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) # This is necessary with JPEG images only
        img = np.expand_dims(img, axis=0) # This is to add one more dimension, batch = 1

        print('INFO: Save: ./npy/inputs/' + img_id + 'x3.npy')
        np.save('./npy/inputs/' + img_id + 'x3.npy', img[0])

        print('INFO: Save: ./csv/inputs/' + img_id + 'x3.csv')
        f = open('csv/inputs/' + img_id + 'x3.csv', 'w')
        writer = csv.writer(f)
        writer.writerow(img[0].flatten())
        f.close()

        # Load pre-trained model (.PB)
        MODEL_DIR = './model/best_status'
        model = tf.keras.models.load_model(MODEL_DIR)
        #model.summary()

        # Run model prediction
        y_keras = model.predict(img)

        print('INFO: Save: ./npy/outputs/' + img_id + '.npy')
        np.save('./npy/outputs/' + img_id, y_keras[0])

        print('INFO: Save: ./png/outputs/' + img_id + '.png')
        cv2.imwrite('./png/outputs/' + img_id + '.png', y_keras[0])

        print('INFO: Save: ./csv/outputs/' + img_id + '.csv')
        f = open('csv/outputs/' + img_id + '.csv', 'w')
        writer = csv.writer(f)
        writer.writerow(y_keras[0].flatten())
        f.close()


