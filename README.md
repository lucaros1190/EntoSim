

# EntoSim v2.1

### Introduction

EntoSim is a software that fit with the idea of a fast application of mathematical models to study ectotherm populations like insects.
It is developed to manage directly all the calculation needed from a first step of lab rearing parameters estimation, to a second step of field population modelling, and finally ending up to a comparison and model validation.  	
All these mathematical operations and analysis are combined in a single software, with the possibility to easily add other population dynamics models, as well as other development rate functions.   
For further reading please refer to [Rossini et al. 2020]( https://www.sciencedirect.com/science/article/pii/S0261219419303709 ).
	
### What is new

We are proud to annouce that the realeas of a new version of EntoSim!
You can now visualize your simulations on your local browsers just by running the EntoSim Docker container without any further installation.

### Background information
If you are not familiar with the mathematical models involved in this software, you can find all the information in the following publications:

1. [Use of ROOT to build a software optimized for parameter estimation and simulations with Distributed Delay Model.](https://www.sciencedirect.com/science/article/pii/S1574954118301420?via%3Dihub)
2. [A novel modelling approach to describe an insect life cycle vis-à-vis plant protection: description and application in the case study of Tuta absoluta.](https://www.sciencedirect.com/science/article/pii/S0304380019302868?via%3Dihubn)
3. [A novel version of the Von Foerster equation to describe poikilothermic organisms including physiological age and reproduction rate.](https://link.springer.com/article/10.1007/s11587-020-00489-6)
4. [EntoSim, a ROOT-based simulator to forecast insects’ life cycle: Description and application in the case of Lobesia botrana.](https://www.sciencedirect.com/science/article/pii/S0261219419303709?via%3Dihub)
5. [Distributed Delay Model and Von Foerster's equation: Different points of view to describe insects' life cycles with chronological age and physiological time.](https://www.sciencedirect.com/science/article/pii/S1574954120300674?via%3Dihub)
6. [A Modelling Approach to Describe the Anthonomus eugenii (Coleoptera: Curculionidae) Life Cycle in Plant Protection: A Priori and a Posteriori Analysis.](https://bioone.org/journals/florida-entomologist/volume-103/issue-2/024.103.0217/A-Modelling-Approach-to-Describe-the-Anthonomus-eugenii-Coleoptera/10.1653/024.103.0217.full)

If you are using EntoSim for scientific purposes, you can cite any of these articles. In particular, the state of art of EntoSim is detailed in (1) and (4), while mathematical aspects are detailed in (2), (3), (5) and (6).

## Requirements
To run the EntoSim v2.1 Docker container you only need:
* Linux OS or MacOS
* Docker version 19.03.12
* Up to 2GB of space.

If you decide that your life is boring and you want to get in trouble, you can clone the repository and install all the required dependancies.
Note that the Python packages can be also installed during [Entosim compiling](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/compiling.md).

* [ROOT v6.16 or later](https://root.cern/)
* [Python 3.0 or later](https://www.python.org/)
* Python 3 packages:
    * numpy
    * scipy
    * plotly
    * dash
    * pandas
    * dash-bootstrap-components
* [GNU Make 3.81 or later](https://www.gnu.org/software/make/)

## Docs
* [Pipeline and Docker tutorial](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/docker_tutorial.md)
* [Compile EntoSim without Docker](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/compiling.md)
* [EntoSim tutorial](https://github.com/lucaros1190/EntoSim-2.1/blob/master/docs/entosim_tutorial.md)

## Developers and contacts
If you have suggestions, complains, if you just want to tell us how awesome we are or want to send us candies, please send us an email: [Luca](mailto:luca.rossini@unitus.it) or [Silvia](mailto:silvia.turco@unitus.it). 
  
## Citation
If you use this software please cite:

	 Rossini L, Turco S. EntoSim 2.1 (Manuscript work in progress)

