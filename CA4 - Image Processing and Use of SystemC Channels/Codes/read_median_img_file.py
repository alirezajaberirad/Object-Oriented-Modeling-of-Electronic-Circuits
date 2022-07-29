import numpy as np
from PIL import Image

if __name__ == "__main__":
	f_name = ["red_median.txt", "green_median.txt", "blue_median.txt"]
	files = []
	for i in f_name:
		files.append(open(i))

	channels = []
	for f in files:
		tmp = f.readlines()
		tmp = np.array([int(i) for i in tmp])
		channels.append(tmp.reshape(510, 510, 1))

	img_np = np.concatenate((channels[0], channels[1], channels[2]), axis=2)
	img = Image.fromarray(img_np.astype("uint8"), "RGB")
	img.show()