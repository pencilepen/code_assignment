#!/usr/bin/env python3
import sys
import argparse
import fileinput
class UVroff:
	def __init__(self,f,s):
		self.filename = f
		self.list_string = s
		self.strings = ' '#return value , output
		self.lines = []#return value , output
	
	def get_file(self):
		return self.filename
	def get_list_strings(self):
		return self.list_string	
	def get_strings(self):
		return self.strings
	##############################
	def lw_default(self,line):
		line = line.rstrip()
		self.lines.append(line)
		self.lines.append('\n')
		#print(line,end='')
	def lw(self,cmdwithvalue,word_list,pre_number,index,filelines):
		
		number = cmdwithvalue[".LW"]
		number -= cmdwithvalue[".LM"]
		width = number - pre_number
		index_word_list = 0
		for ele in word_list:
			index_word_list +=1
			#print('ele',ele)
			#print('width',width)
			if width > len(ele):
				ele += ' '
				self.strings += ele
				#print(ele+" ",end='')#output words inside lw, no chang line
				width-=len(ele)
				#width-=1
				
				if width == 0:
					self.strings = self.strings[1:-1]
					self.lines.append(self.strings)
					#self.lines.append('\n')
					self.strings = ' '
				
			elif width == len(ele):
				
				self.strings+=ele
				self.strings = self.strings[1:]
				self.lines.append(self.strings)
				
				self.lines.append('\n')
				self.strings = ' '
				#print(ele,end='')#output at end of lw,chang line
				#print()
				width = number
				self.ls(cmdwithvalue[".LS"],index, filelines)
				self.lm(cmdwithvalue[".LM"],cmdwithvalue)
				
			else:
				ele = ele.rstrip()
				if width < len(ele):#ouput the word at next line after chang line 
					self.strings = self.strings.rstrip()
					self.strings = self.strings[1:]
					self.lines.append(self.strings)
					self.lines.append('\n')
					#print()
					self.strings = ' '
					width=number
					self.ls(cmdwithvalue[".LS"],index, filelines)
					self.lm(cmdwithvalue[".LM"],cmdwithvalue)
					ele += ' '
					self.strings += ele
					
					#print(ele+" ",end='')
					width-=len(ele)
		try:
			filelines[index]
			
		except:
			self.strings=self.strings[1:]
			self.strings.rstrip()
			self.lines.append(self.strings)
			self.strings = ' '
			########################
			#self.lines.append('\n')
			#print()
		pre_number = number - width
		return pre_number
	def lm(self,number,cmdwithvalue):
		if cmdwithvalue[".LM"]<0:
			number = 0
		elif cmdwithvalue[".LM"] > (cmdwithvalue[".LW"]-20):
			number = (cmdwithvalue[".LW"] - 20)
		self.strings += (' '*number)
		#print(" "*number,end='')
	def ls(self,number,index,filelines):
		try :
			filelines[index]
		except:
			return 

		while number > 0:
			self.lines.append('\n')
			#print()
			number-=1
	def get_lines(self):
		filename = self.filename
		pre_number = 0
		cmdwithvalue = {'.LW': 0, '.LM': 0, '.LS': 0, '.FT': 'on'}
		#####################
		try:
			f = open(filename,"r")
		except IOError:
			for ele in self.list_string:
				self.strings +=ele
				#print(ele+' ',end='')
			#print()
			self.strings = self.strings[1:]
			return
		index = 0
		changeline=0
		changeline_check = changeline
		filelines=f.readlines()
		for line in filelines:
			index += 1
			if line == "\n": 
			##################
				self.strings = self.strings[1:-1]
				self.lines.append(self.strings)
				self.lines.append('\n')
				self.strings = ' '
				#####################3
				changeline += 1
				self.ls(cmdwithvalue[".LS"],index, filelines)
				self.lines.append('\n')
				
				#print("chang line 2222222222222222223333")
				#print()
				#print()
				self.ls(cmdwithvalue[".LS"],index, filelines)
				pre_number = 0
				continue
				
			word_list = line.strip().split()
		
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
							self.lm(cmdwithvalue[".LM"],cmdwithvalue)
			else:#print 
			
				if cmdwithvalue[".LW"] == 0:# no .LW 
					cmdwithvalue[".FT"]="off"
				if cmdwithvalue[".FT"][-2]=="f":#
					self.lw_default(line)
				else:# there is  .LW 
					if changeline != changeline_check:
						self.lm(cmdwithvalue[".LM"],cmdwithvalue)
					
					pre_number = self.lw(cmdwithvalue,word_list,pre_number,index,filelines)	
			changeline_check = changeline
		f.close()
		
		for  ele in self.lines:
			
			self.strings +=ele
		self.strings = self.strings[1:-1]	
		self.lines.clear()
		self.lines.append(self.strings)
		return self.lines