import tweepy
import glob
import random
import os
import subprocess
from subprocess import Popen, PIPE
import time
#Personal, every user should complete.
api_key = ""
api_secret = ""
oauth_token = "" # Access Token
oauth_token_secret = "" # Access Token Secret
auth = tweepy.OAuthHandler(api_key, api_secret)
auth.set_access_token(oauth_token, oauth_token_secret)
api = tweepy.API(auth)
#Changes directory to where the script is located (easier cron scheduling, allows you to work with relative paths)
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)
def randomimagetwitt(folder):
	#Takes the folder where your images are as the input and twitts one random file.
	images = glob.glob(folder + "*")
	print images, "HERE"
	image_open = images[random.randint(0,len(images))-1]
	api.update_with_media(image_open)


# a = subprocess.call("./bin/myJubilantSketch.app/Contents/MacOS/myJubilantSketch")
# if a != 0: print "OOOOOPPPPSSSSS"

# randomimagetwitt("/Users/ebernitsas/Desktop/OF/apps/myApps/myJubilantSketch/bin/data/test.gif")

#=======================================

startTime = time.time()
while (True):
	currTime = time.time()
	if ((currTime - startTime) > 600):
		#Twitts
		a = subprocess.call("./bin/myJubilantSketch.app/Contents/MacOS/myJubilantSketch")
		if a != 0: print "OOOOOPPPPSSSSS"

		randomimagetwitt("/Users/ebernitsas/Desktop/OF/apps/myApps/myJubilantSketch/bin/data/test.gif")
		startTime = time.time()





