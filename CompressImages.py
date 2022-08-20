from PIL import Image
import os

class Compress_img:

    def __init__(self, img_path):
        self.img_path = img_path
        self.img_name = img_path.split('/')[-1]

    def compress_img_PIL(self, compress_rate=0.4):
        img = Image.open(self.img_path)
        w, h = img.size
        # 使用resize改变图片分辨率，但是图片内容并不丢失，不是裁剪
        img_resize = img.resize((int(w*compress_rate), int(h*compress_rate)))
        resize_w, resieze_h = img_resize.size
        if not os.path.exists('./compress_output'):
            os.mkdir('./compress_output')
        img_resize.save('./compress_output/' + self.img_name)
        print("%s 已压缩，" % (self.img_name), "压缩率：", compress_rate)


if __name__ == '__main__':
    # 输入压缩率
    rate = eval(input("Please input the compress rate (default:0.4):"))

    for filename in os.listdir(os.getcwd()):
        if (os.path.splitext(filename)[1] == '.png'):   # 过滤png图片
            path = './' + filename
            cmp = Compress_img(path)
            cmp.compress_img_PIL(rate)
