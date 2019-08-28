import os


def get_edge_list(dataset, file_name, split_type, start_line=0):
	# edge_data = open(dataset+"/experiments/"+file_name,"r").readlines()[start_line:]
	edge_data = open(file_name,"r").readlines()[start_line:]
	edge_list = []
	# node_num = 100000
	for edge_str in edge_data:
		edge_str = edge_str.replace("r","").replace("n","")
		if split_type == 1:
			edge_items = edge_str.split("\t")
			edge_list.append((int(edge_items[0]),int(edge_items[1])))
		elif split_type == 2: # src type tgt
			edge_items = edge_str.split(" ")
			edge_list.append((int(edge_items[0]),int(edge_items[2])))
		else: # src tgt1 tgt2 ..
			edge_items = edge_str.split(" ")
			src_node = int(edge_items[0])
			if len(edge_items) < 2:
				continue
			for target_node in edge_items[1:]:
				if target_node == '':
					continue
				edge_list.append((src_node,int(target_node)))
	return edge_list


def calculate_degree(edge_list, edge_type):
	if edge_type == "directed":
		indegree_dic = {}
		outdegree_dic = {}
		for edge in edge_list:
			src_node = edge[0]
			target_node = edge[1]
			if target_node not in indegree_dic:
				indegree_dic[target_node] = 1
			else:
				indegree_dic[target_node] += 1
			if src_node not in outdegree_dic:
				outdegree_dic[src_node] = 1
			else:
				outdegree_dic[src_node] += 1

		indegree_node_dic = {}
		outdegree_node_dic = {}
		for node in indegree_dic:
			indegree = indegree_dic[node]
			if indegree not in indegree_node_dic:
				indegree_node_dic[indegree] = 1
			else:
				indegree_node_dic[indegree] += 1
		for node in outdegree_dic:
			outdegree = outdegree_dic[node]
			if outdegree not in outdegree_node_dic:
				outdegree_node_dic[outdegree] = 1
			else:
				outdegree_node_dic[outdegree] += 1

		return (indegree_node_dic,outdegree_node_dic)
	else:
		degree_dic = {}
		for edge in edge_list:
			src_node = edge[0]
			target_node = edge[1]
			if src_node not in degree_dic:
				degree_dic[src_node] = 1
			else:
				degree_dic[src_node] += 1
			if target_node not in degree_dic:
				degree_dic[target_node] = 1
			else:
				degree_dic[target_node] += 1

		degree_node_dic = {}
		for node in degree_dic:
			degree = degree_dic[node]
			if degree not in degree_node_dic:
				degree_node_dic[degree] = 1
			else:
				degree_node_dic[degree] += 1
		return degree_node_dic



def output_directed(filename,indegree_node_dic,outdegree_node_dic):
	# indegree_file = open(dataset+"/experiments/indegree.txt","w")
	basename = os.path.basename(filename).split('.')[0]
	indegree_file = open(basename + "_indegree.txt","w")
	indegree_write_str = ""
	for indegree in indegree_node_dic:
		indegree_write_str += str(indegree) + "\t" + str(indegree_node_dic[indegree]) + "\n"
	indegree_file.write(indegree_write_str)
	indegree_file.close()

	outdegree_file = open(basename + "_outdegree.txt","w")
	outdegree_write_str = ""
	for outdegree in outdegree_node_dic:
		outdegree_write_str += str(outdegree) + "\t" + str(outdegree_node_dic[outdegree]) + "\n"
	outdegree_file.write(outdegree_write_str)
	outdegree_file.close()


def output_undirected(filename,degree_node_dic):
	# degree_file = open(dataset+"/experiments/degree.txt","w")
	basename = os.path.basename(filename).split('.')[0]
	degree_file = open(basename + "_degree.txt","w")
	degree_write_str = ""
	for degree in degree_node_dic:
		degree_write_str += str(degree) + "\t" + str(degree_node_dic[degree]) + "\n"
	degree_file.write(degree_write_str)
	degree_file.close()



def main(dataset_list, file_name_list, split_type_list):
	dataset_num = len(dataset_list)
	for i in range(dataset_num):
		print(dataset_list[i])
		if dataset_list[i] == "FastKronecker":
			edge_list = get_edge_list(dataset_list[i],file_name_list[i],split_type_list[i],4)
		else:
			edge_list = get_edge_list(dataset_list[i],file_name_list[i],split_type_list[i])
		print("load data done ...")
		if dataset_list[i] == "ROLL": # undirected edges
		# if dataset_list[i] == "test": # undirected edges
			degree_node_dic = calculate_degree(edge_list, "undirected")
			# print(degree_node_dic)
			print("calculate degrees done ...")
			output_undirected(file_name_list[i],degree_node_dic)
		else:
			indegree_node_dic,outdegree_node_dic = calculate_degree(edge_list, "directed")
			print("calculate degrees done ...")
			# print(indegree_node_dic)
			# print(outdegree_node_dic)
			output_directed(file_name_list[i],indegree_node_dic,outdegree_node_dic)
		print("output done ...")


if __name__ == '__main__':
	# dataset_list = ["test"]
	# file_name_list = ["graph.txt"]
	# split_type_list = [1]
	# main(dataset_list, file_name_list, split_type_list)


	# dataset_list = ["FastKronecker", "gMark", "LFR", "RMat", "ROLL", "SNG", "TrillionG"]
	# file_name_list = ["g100K.txt", "graph70.txt", "g100K.txt", "g100K.txt", "g100K.txt", "g100K.txt", "g100K/part-00000"]
	# split_type_list = [1, 2, 1, 1, 1, 3, 1]
	# main(dataset_list[5:], file_name_list[5:], split_type_list[5:])
	
	# dataset_list = ["./", "./", "./", "./", "./", "./", "./", "./", "./", "./"]
	# file_name_list = ["data_0.adj", "data_1.adj", "data_2.adj", "data_3.adj", "data_4.adj", "data_5.adj", "data_6.adj", "data_7.adj", "data_8.adj", "data_9.adj"]
	# split_type_list = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
	# main(dataset_list, file_name_list, split_type_list)
	
	dataset_list = ["./"]
	# filename_list = ["exp1.adj"]
	filename_list = ["exp1.adj"]
	split_list = [3]
	main(dataset_list, filename_list, split_list)

