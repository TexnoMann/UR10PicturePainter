import pandas as pd
import os
import kdl_parser_py.urdf

df_list = []
for file in os.listdir(your_directory):
    df = pd.read_csv(file)
	df_list.append(df)
    for index, row in df.iterrows():
