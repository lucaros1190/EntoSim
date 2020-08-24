## EntoSim v2.1 Docker setup

### Download and install Docker
Download [Docker](https://www.docker.com/get-docker) and
follow the official [installation instructions](https://docs.docker.com/install/).

### Download EntoSim image from docker hub

1. Open a terminal:
	* __HOST:__
  
			$ sudo docker pull lucaros1190/entosim:v2.1 

2. Check that you succesfully download the image:
	* __HOST:__
  
			$ sudo docker images

3. If there is more than one image from the repository __biologger/speciesprimer__, you can remove the image with the <none\> Tag
 	* __HOST:__
 
			$ sudo docker rmi {image_id}
