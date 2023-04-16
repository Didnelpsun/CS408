from dataclasses import replace
import os
import datetime,time
import shutil


path = "E:\考研专业课\笔记\CS408-main\Data-Structrue\课本"


#制造独一无二的文件名

#获取当前时间
now_time = datetime.datetime.now()

#格式化时间字符串
str_time = now_time.strftime("%Y-%m-%d %H_%M_%S")

#初始化默认文件名
name = "Combine-.md"

#合并为输出文件名
name_mid = list(name)
name_mid.insert(8,str_time)
name_new = "".join(name_mid)

#按照WINDOWS文件名规则审查输出
name_new = name_new.replace('?', '').replace('*', '').replace('<', '').replace('> ', '')


print('{}'.format(name_new)) #debug

'''
当需要批量命名时，可不使用时间戳命名而改为以下方式命名（批量赋予数字）

'''
# name_template = '{:0>3d}'#设置编号格式化为3位

# num = 0 #记录文件数量

md_list = os.listdir(path)

contents = []
for md in md_list:
    md_file = path + '\\' + md
    with open(md_file, 'r', encoding='utf-8',errors='ignore') as file: #此处忽略错误，可能导致某些格式无法支持，如png
        contents.append(file.read() + "\n")

with open(path+'\{}'.format(name_new), "w", encoding='utf-8') as file: #保存在原位置
    '''
    批量命名的输出语句
    '''
# with open('Merge_'+name_template.format(++ num)+'.md', "w", encoding='utf-8') as file:
    file.writelines(contents)

