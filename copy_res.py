import os
import shutil

src_dir = "D:/workspace_cocos/G2048Simple_content/res"
dst_dir = "Resources"

def deleteFolderIfExist(path):
	if(os.path.exists(path)):
		shutil.rmtree(path)

def createFolderIfNoExist(path):
	if not os.path.exists(path):
		os.mkdir(path)

def copy_file(src_file, dst_file):
	shutil.copy(src_file, dst_file)

def copy_file_in_folder (srcFolder, desFolder):
	for file_name in os.listdir(srcFolder):
		src_file = os.path.join(srcFolder, file_name)
		dst_file = os.path.join(desFolder, file_name)
		if(os.path.isfile(src_file)):
			print(src_file)
			copy_file(src_file, dst_file)
		else:
			createFolderIfNoExist(dst_file)
			copy_file_in_folder(src_file, dst_file)

def main():
	deleteFolderIfExist(dst_dir)
	createFolderIfNoExist(dst_dir)
	copy_file_in_folder(src_dir, dst_dir)
	
main()