import os
import shutil

src_dir = "D:/workspace_cocos/G4096/Classes"
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
			
def list_file_in_folder(srcFolder, parentFolder, androidMk):
	for file_name in os.listdir(srcFolder):
		file = os.path.join(srcFolder, file_name)
		if(os.path.isfile(file)):
			if(".cpp" in file):
				relativePath = file.replace(parentFolder, "/../../..").replace("\\","/")
				androidMk.write("$(LOCAL_PATH)"+relativePath+"\\\n");
				print("$(LOCAL_PATH)"+relativePath+"\\")
		else:
			list_file_in_folder(file, parentFolder, androidMk)

def main():
	#deleteFolderIfExist(dst_dir)
	#createFolderIfNoExist(dst_dir)
	#copy_file_in_folder(src_dir, dst_dir)
	parentFolder = os.path.abspath(os.path.join(src_dir, os.pardir))
	print(parentFolder)
	androidMk = open("androidMkTmp.txt","w") 
	list_file_in_folder("D:\\workspace_cocos\\G4096\\Classes", parentFolder, androidMk)
	androidMk.close()
	x = raw_input("Press anything")
	print("hello "+x)
	
main()