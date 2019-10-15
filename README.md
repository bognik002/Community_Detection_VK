# Community_Detection_VK
This project is the Summer Practice task. There I tried to achieve an application, which draws a friend's graph of a community in vk.com,
then apply different algorithms to this data in order to detect subcommunity inside the initial vk community.

The essential files are:
1) data_download - is a program, which uses VK_API to collect the data about the group subscribers, connect each of them with their friends
in the group
2) data_process - is a program, which using the data that has been collected by the data_download construct a graph of friends and
store it in a csv file entered in the beggining of the program
3) kargers_algorithm - is a programm, which applies the Karger's algorithm to detect the bottleneck (minimal cut) inside the graph,
by which the two subgrouops are separated
4) data_drawing exports the data achieved on the previous steps into csv file to draw it using the Gephi application for drawing graphs

The results of the program are discribed in the Report.docx and Presentation.pptx
The csv files processed are stored in the data folder, the pictures of the graphs are stored into Screenshots
