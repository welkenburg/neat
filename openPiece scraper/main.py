from selenium import webdriver
import time
import requests

def download(url,i):
	"""
	download the ith episode of onepiece with the url
	"""
	print("url :",url)
	r = requests.get(url, stream=True)
	with open(f"episodes/one piece {i}.mp4", 'wb') as f:
		for chunk in r.iter_content(chunk_size=1024):
			if chunk:
				f.write(chunk)
	print(f"video {i} finished")

startEp = int(input("Episode de départ ?\n"))
endEp = int(input("Episode de fin ?\n"))

driver = webdriver.Chrome("chromedriver.exe")
for i in range(startEp,endEp):
	driver.get(f"https://gogoanime.so/one-piece-episode-{i}")
	
	src = ""
	while src == "":
		#switch to the first tab
		driver.switch_to.window(driver.window_handles[0])

		#get the video link
		iframe = driver.find_element_by_xpath("/html/body/div[2]/div/div/section/section[1]/div[1]/div[2]/div[3]/div/div/div/iframe")
		driver.switch_to.frame(iframe)

		time.sleep(3)
		video = driver.find_element_by_tag_name("video")
		src = video.get_attribute('src')
		try:
			download(src,i)
		except:
			#print("error empty url")
			pass

	#refocus on the whole page
	driver.switch_to.default_content()

#when the program ends, the tabs close
driver.close()
