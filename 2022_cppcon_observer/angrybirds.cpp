// Pseudo code -- angrybirds.cpp
void BirdSlingshot(){
	
	SimulateBirdPhysics(...)

	if(CheckCollisions()){
		PlaySoundBirdNoise()

		if(HitObject Pig){
			UpdateScore();

			PlayPigSound();

			SimulateObjectPhysics(pig)
		}
	
		LogResult();
	}
}


