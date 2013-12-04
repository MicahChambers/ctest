#include <iostream>
#include <cmath>
#include <memory>
#include <list>
#include <map>

using namespace std;

class LineSearcher
{
	public:
		LineSearcher(double left, double right, double xres, double yres) 
		{
			m_minxrange = xres;
			m_minyrange = yres;
			m_queue.push_back(left);
			m_queue.push_back(right);
		};

		void getBest(double* xbest, double* ybest)
		{
			auto maxit = m_done.begin(); //points to the point after the largest gap
			double maxval = -INFINITY; 
			for(auto it = m_done.begin(); it != m_done.end(); it++) {
				if(it->second > maxval) {
					maxval = it->second;
					maxit = it;
				}
			}
			*xbest = maxit->first;
			*ybest = maxit->second;
		};

		bool getNextX(double* nextx)
		{
			//this is sort of overly complicated to create a grid of 
			//search points, but I may switch to alternating between y
			//and x searches, in which case this would be necesssary
			if(m_queue.empty()) {
				//search in largest x range
				auto it = m_done.begin(); //just the iterator
				auto gap = m_done.begin(); //points to the point after the largest gap
				double prev = it->first; 
				double maxgap = 0; 
				it++;
				for(; it != m_done.end(); it++) {
					double x = it->first;
					if(x-prev > maxgap) {
						maxgap = x-prev;
						gap = it;
					}
					prev = x;
				}

				double b = gap->first;
				--gap;
				double a = gap->first;

				if(fabs(b-a) >= m_minxrange) 
					m_queue.push_back((b+a)/2.);
			} 
			
			//if queue is still empty, switch to searching around max
			if(m_queue.empty()) {
				//add points on each side of the largest point (if applicable)
				auto maxit = m_done.begin(); //points to the point after the largest gap
				double maxval = -INFINITY; 
				for(auto it = m_done.begin(); it != m_done.end(); it++) {
					if(it->second > maxval) {
						maxval = it->second;
						maxit = it;
					}
				}

				//add the point after the max
				double a = maxit->first;
				double ay = maxit->second;
				if(maxit != m_done.end()) {
					maxit++;

					if(fabs(ay-maxit->second) > m_minyrange) 
						m_queue.push_back((maxit->first+a)/2.);

					maxit--;
				}

				if(maxit != m_done.begin()) {
					maxit--;

					if(fabs(ay-maxit->second) > m_minyrange) 
						m_queue.push_back((maxit->first+a)/2.);

					maxit++;
				}
			}
			
			if(m_queue.empty())
				return true;//all done

			*nextx = m_queue.front();
			m_queue.pop_front();
			return false;
		};

		bool addResult(double x, double y) 
		{
			m_done[x] = y;
		};

	private:
		double m_minxrange;
		double m_minyrange;
		
		list<double> m_queue;
		map<double, double> m_done;
};

int main()
{
	bool done = false;
	LineSearcher searcher(-4, 4, 1, .1);
	double x;
	for(int ii = 0 ; ii < 100 && !done; ii++) {
		done = searcher.getNextX(&x);
		if(!done) 
			searcher.addResult(x, sin(x));
	}

	double y;
	searcher.getBest(&x,&y);
	cout << "Best Result: " << x << "," << y << endl;
}
