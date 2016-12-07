This is the VS2015 project folder for the default sample setup.

To run this empty sample in VS2015 take the following steps:

1. Download and extract the vs_extended bundle.
---------------------------------------------------------------------
Download vs_2015_v2_2016_2017.zip from Blackboard
Extract it somewhere on your harddrive.

2. Download and install VS2015:
---------------------------------
https://www.visualstudio.com/downloads/

* Open up sample_paths.props in your text editor:
	* Update the include and lib folder to where you extracted the vs_extended bundle
* Open up the project sln or vxproj
* Select one of the build targets (debug/release & dynamic/static) and build the engine.
* In case your version complains about missing dll's, copy all files from the vs_extended\bin folder to your exe folder.

Deploying your game?
--------------------
Build a release version, copy all dll's in case you chose the dynamic version and assets to the same folder, zip and deploy.

Setting up your own vs project?
------------------------------------------------------
Copy the this folder structure but replace the sources.

