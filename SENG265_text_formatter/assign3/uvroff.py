#!/usr/bin/env python3
import fileinput
import sys


def lw_default(line):
	print(line,end='')
	#for ele in word_list:
	#	print(ele+' ', end='')
	#print()
	
def lw(cmdwithvalue,word_list,pre_number,index,filelines):
	number = cmdwithvalue[".LW"]
	number -= cmdwithvalue[".LM"]
	width = number - pre_number
	for ele in word_list:
		if width > len(ele):
			print(ele+" ",end='')#output words inside lw, no chang line
			width-=len(ele)
			width-=1
			
		elif width == len(ele):
			print(ele,end='')#output at end of lw,chang line
			print()
			width = number
			ls(cmdwithvalue[".LS"],index, filelines)
			lm(cmdwithvalue[".LM"],cmdwithvalue)
		else:
			if width < len(ele):#ouput the word at next line after chang line 
				print()
				width=number
				ls(cmdwithvalue[".LS"],index, filelines)
				lm(cmdwithvalue[".LM"],cmdwithvalue)
				print(ele+" ",end='')
				width-=len(ele)
				width-=1
	try:
		filelines[index]
	except:
		print()
	pre_number = number - width
	return pre_number
def lm(number,cmdwithvalue):
	if cmdwithvalue[".LM"]<0:
		number = 0
	elif cmdwithvalue[".LM"] > (cmdwithvalue[".LW"]-20):
		 number = (cmdwithvalue[".LW"] - 20)
	#print(".LM number", number,end='')
	print(" "*number,end='')
def ls(number,index,filelines):
	try :
		filelines[index]
	except:
		return 

	while number > 0:
		print()
		number-=1
	
def main():
	filename=sys.argv[1]
	
	pre_number = 0
	cmdwithvalue = {'.LW': 0, '.LM': 0, '.LS': 0, '.FT': 'on'}
	#####################
	try:
		f = open(filename,"r")
	except IOError:
		for ele in sys.argv[1:]:
			print(ele+' ',end='')
		print()
		return
	index = 0
	changeline=0
	changeline_check = changeline
	filelines=f.readlines()
	for line in filelines:
		index += 1
		if line == "\n": 
			changeline += 1
			ls(cmdwithvalue[".LS"],index, filelines)
			print()
			print()
			ls(cmdwithvalue[".LS"],index, filelines)
			pre_number = 0
			continue
		
		word_list = line.strip().split(" ")
		
		pre_lmnumber=cmdwithvalue[".LM"]
		if word_list[0] in cmdwithvalue:
			if word_list[1][0] == '+' or word_list[1][0] == '-':
				cmdwithvalue[".LM"] += int(word_list[1])
			else:
				try:
					cmdwithvalue[word_list[0]] = int(word_list[1])#store command value 
				except:
					cmdwithvalue[".FT"]=word_list[1]
			if pre_lmnumber != cmdwithvalue[".LM"] or changeline_check != changeline:
				if filelines[index].find(".LM") == -1: 
					if word_list[0] != ".FT" and cmdwithvalue[".LM"] != 0:
						lm(cmdwithvalue[".LM"],cmdwithvalue)
					
		else:#print 
			
			if cmdwithvalue[".LW"] == 0:# no .LW 
				cmdwithvalue[".FT"]="off"
			if cmdwithvalue[".FT"][-2]=="f":#
				lw_default(line)
			else:# there is  .LW 
				if changeline != changeline_check:
					lm(cmdwithvalue[".LM"],cmdwithvalue)
					
				pre_number = lw(cmdwithvalue,word_list,pre_number,index,filelines)
				#print("lw cmd with value 2222222222222222")
		changeline_check = changeline
	f.close()

if __name__ == "__main__":
	main()




