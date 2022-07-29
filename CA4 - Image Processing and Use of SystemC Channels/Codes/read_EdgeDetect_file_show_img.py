from PIL import Image
import numpy as np

if __name__ == "__main__":
	file_name = "finalPicture1.txt"
	img_f = open(file_name)

	tmp = img_f.readlines()
	gray_scale_img = [int(i[:-1]) for i in tmp]

	gray_scale_img = (np.array(gray_scale_img)).reshape(510,-1)
	print(gray_scale_img.shape)
	img = Image.fromarray(gray_scale_img.astype("uint8"), 'L')
	img.show()






