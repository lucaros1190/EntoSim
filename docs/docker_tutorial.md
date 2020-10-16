## EntoSim v2.1 Docker setup

### Download and install Docker
Download [Docker](https://www.docker.com/get-docker) and
follow the official [installation instructions](https://docs.docker.com/install/).
If Docker is already installed in your system, try to run the hello-world image to verify that everything is working and you have the right permission to run Docker (if not, contact your SysAdmin).

			$ docker run hello-world
			

### Download EntoSim image from docker hub

1. Open a terminal:
	* __HOST:__
	
			$ docker pull lucaros1190/entosim:v2.1 

2. Check that you succesfully download the image:
	* __HOST:__
  
			$ docker images

3. If you decide you don't need EntoSim image anymore (and we would be very sad about that), you can remove it with:
	
	* __HOST:__
 
			$ docker rmi lucaros1190/entosim:v2.1 

### Get ready to run EntoSim
4. Create your working directory on your local host, let's say *yourhomefolder/EntoSim-data*. This folder is required to transfer your personal input and output data from and to the container. Once you have added files, you can copy into the specific folders, as explained in the [EntoSim tutorial](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md). You are free to use any other folder name, but remember to change it in the rest of the pipeline accordingly.
	* __HOST:__
 
			$ mkdir -p EntoSim-data/ 

5. Don't forget that this folder is just a bridge from your local machine and EntoSim container. Once you have placed your input data inside, for instance, you should copy them in EntoSim-2.1/input/ folder, paying attention to the names and formattation. For the detailed description of the input/output files, have a look at the EntoSim Functions below.

### Start the EntoSim container
6. Let's start this adventure by typing:
	* __HOST:__
 
			$  docker run -ti --rm -p 8080:8080 -v your_local_directory_path:/home/EntoSim-2.1/EntoSim-data lucaros1190/entosim:v2.1 

* You obviously need to run the container in an interactive mode and to remove it when you are done use the --rm option. 
* To visualize the interactive graph generated during the simulations (and thus, to be able to reach the mighty web) you need to expose the port 8080.
* To mount the folders you created in the previous step, use the -v command. Note that you are free to change these paths, but then don't go to mommy to cry. "With great freedom comes great responsibility".
* Give your container a name and specify the Docker images you want to use.

If everything worked properly, your prompt should be something like this:

			[root@dockerID EntoSim-2.1]# 

You are finally ready to play with your insects! Jump to [EntoSim tutorial](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md)

Please notice that the folder 'EntoSim-data' is just a bridge between your local machine and the container where EntoSim is running. If you need to save your outputs on your local machine, for example, just copy the output folder in EntoSim-data folder:

			cp -r /home/EntoSim-2.1/output/ /home/EntoSim-data/

Now, let us suppose that you want to upload a particular input file. Remember that the names of the files and the data inside need to be written "as EntoSim wants" (refer to [EntoSim tutorial](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md)). To provide an example of "upload input files" let us consider the DailyTemperatures.txt file (the operations are exactly the same, just change the input file name!). Place your edited DailyTemperatures.txt file in your local machine EntoSim-data folder ($HOME/EntoSim-data). From the container just type:

			cp /home/EntoSim-data/DailyTemperatures.txt /home/Entosim-2.1/input/
			
			 


