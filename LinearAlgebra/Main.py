from PIL import Image, ImageDraw
import numpy as np

def read_image_as_array(image_path):
    """读取图像并转换为灰度数组"""
    return np.array(Image.open(image_path).convert('L'))

def template_match_ccoeff_normed(big_image, template):
    """使用 CCOEFF_NORMED 方法进行匹配"""
    h_big, w_big = big_image.shape
    h_temp, w_temp = template.shape

    # 准备存储运算结果的矩阵
    result = np.zeros((h_big - h_temp + 1, w_big - w_temp + 1))

    # 对模板图进行标准化
    normed_template = (template - template.mean()) / template.std()

    # 遍历大图像
    for y in range(result.shape[0]):
        for x in range(result.shape[1]):
            # 提取当前感受野中的子图像
            window = big_image[y:y + h_temp, x:x + w_temp]
            # 对子图像进行标准化
            window_std = window.std()
            if window_std > 0:
                normed_window = (window - window.mean()) / window_std
                # 计算 CCOEFF_NORMED：
                # 分子是点积，分母是向量的模长的乘积，也就是标准差的乘积。
                # 由于我们提前对子图和模板图进行了标准化，所以可以采用下面的算式来计算。
                result[y, x] = (normed_window * normed_template).sum()
            else:
                result[y, x] = 0

    # 运算结果矩阵映射到 [0, 1]
    result /= result.max()
    return result

def visualize_result(big_image_path, template_path, result):
    """匹配结果可视化"""
    big_image = Image.open(big_image_path).convert('RGB')
    template = Image.open(template_path)
    w_temp, h_temp = template.size

    # 找到最大相似值的位置
    max_loc = np.unravel_index(np.argmax(result), result.shape)
    top_left = (max_loc[1], max_loc[0])

    # 绘制一个矩形标注框
    draw = ImageDraw.Draw(big_image)
    right_bottom = (max_loc[1] + w_temp, max_loc[0] + h_temp)
    draw.rectangle([top_left, right_bottom], outline='red', width=3)

    # 保存运算结果图和标注后的大图
    result_image = Image.fromarray(result * 255).convert('L')
    result_image.save(f"Result_{big_image_path}")
    big_image.save(f"Result_Labeled_{big_image_path}")

def main(big_image_path, template_path):
    """主函数"""
    big_image = read_image_as_array(big_image_path)
    template = read_image_as_array(template_path)
    print("正在进行匹配……")
    result = template_match_ccoeff_normed(big_image, template)
    print("匹配完成！")
    visualize_result(big_image_path, template_path, result)

if __name__ == '__main__':
    big_image_path = "Img1.jpg"
    template_path = "Template.jpg"
    main(big_image_path, template_path)
