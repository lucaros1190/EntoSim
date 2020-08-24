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
4. Create your working directory on your local host, let's say yourhomefolder/EntoSim, within you must also add two addictional folders required by the program: /input and /output. 
	* __HOST:__
 
			$ mkdir -p EntoSim/{input,output} 

5. You may also create some input text files to be saved inside the /input folder, where EntoSim is going to look for when needed.
For the detailed description of these files, have a look at the EntoSim Functions below.

### Start the EntoSim container
6. Let's start this adventure by typing:
	* __HOST:__
 
			$  docker run -ti --rm \
			-p 8080:8080 \
			-v $HOME/Entosim/input:/home/Entosim1/input \ 
			-v $HOME/Entosim/output:/home/Entosim1/output \ 
			-w /home/Entosim1 \
			--name Entosim lucaros1190/entosim:v2.1 


