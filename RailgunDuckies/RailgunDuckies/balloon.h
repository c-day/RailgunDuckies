#define BALLOON_H

class balloon {
	private:
		double x, y, z, r;
		float cx, cy, cz;
		double slices, stacks;
		///double vertices[50];
		struct profile {
			double x; 
			double y;
			double z;
		};

		struct profile vertices[36000];

		
	public:
		balloon();
		void drawBalloon();
		void topHalf();
		void bottomHalf();
};