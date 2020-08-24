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

### Create your working directory
 	* __HOST:__
Create a folder, let's say /EntoSim on your local host, within you must also add two addictional folders required by EntoSim: /input and /output. 
You may also create some input text files to be saved inside the /input folders where EntoSim is going to look for them. ** ***

### Start the EntoSim container



