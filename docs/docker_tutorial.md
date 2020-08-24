## EntoSim v2.1 Docker setup

### Download and install Docker
Download [Docker](https://www.docker.com/get-docker) and
follow the official [installation instructions](https://docs.docker.com/install/).
If Docker is alreayd installed in your system, try to run the hello-world image to verify that everything is working and you have the right permission to run Docker (if not, contact your SysAdmin).

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
4. Create your working directory on your local host, let's say yourhomefolder/EntoSim, within you must also add two addictional folders required by the program: /input and /output. You are free to use any other folder name, but remember to modify it in the rest of the pipeline accordingly.
	* __HOST:__
 
			$ mkdir -p EntoSim/{input,output} 

5. You may also create some input text files to be saved inside the /input folder, where EntoSim is going to look for when needed.
For the detailed description of these files, have a look at the EntoSim Functions below.

### Start the EntoSim container
6. Let's start this adventure by typing:
	* __HOST:__
 
			$  docker run -ti --rm \
			-p 8080:8080 \
			-v $HOME/Entosim/input:/home/Entosim/input \ 
			-v $HOME/Entosim/output:/home/Entosim/output \ 
			-w /home/Entosim \
			--name Entosim lucaros1190/entosim:v2.1 

* You obviously need to run the container in an interactive mode and to remove it when you are done use the --rm option. 
* To visualize the interactive graph generated during the simulations (and thus, to be able to reach the mighty web) you need to expose the port 8080.
* To mount the folders you created in the previous step, use the -v command. Note that you are free to change these paths, but then don't go to mommy to cry. "With great freedom comes great responsibility".
* To have everything on your (and its) disposal, set /Entosim as your working directory.
* Give your container a name and specify the Docker images you want to use.

