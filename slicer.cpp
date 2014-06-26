
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

/**
 * @brief This class is used to slice an image in along a dimension, and to 
 * step an arbitrary direction in an image. Order may be any size from 0 to the
 * number of dimensions. The first member of order will be the fastest moving,
 * and the last will be the slowest. Any not dimensions not included in the order
 * vector will be slower than the last member of order
 */
class Slicer 
{
public:

	/**
	 * @brief Default Constructor, max a length 1, dimension 1 slicer
	 */
	Slicer();
	

	/**
	 * @brief Full Featured Constructor
	 *
	 * @param dim	size of ND array
	 * @param order	order of iteration during ++, this doesn't affect step()
	 * @param roi	min/max, roi is pair<size_t,size_t> = [min,max] 
	 */
	Slicer(std::vector<size_t>& dim, std::list<size_t>& order,
			std::vector<std::pair<size_t,size_t>>& roi);

	/**
	 * @brief Simple (no ROI, no order) Constructor
	 *
	 * @param dim	size of ND array
	 */
	Slicer(std::vector<size_t>& dim);
	
	/**
	 * @brief Constructor that takes a dimension and order of ++/-- iteration
	 *
	 * @param dim	size of ND array
	 * @param order	iteration direction, steps will be fastest in the direction
	 * 				of order[0] and slowest in order.back()
	 */
	Slicer(std::vector<size_t>& dim, std::list<size_t>& order);

	/**
	 * @brief Constructor that takes a dimension and region of interest, which
	 * is defined as min,max (inclusive)
	 *
	 * @param dim	size of ND array
	 * @param roi	min/max, roi is pair<size_t,size_t> = [min,max] 
	 */
	Slicer(std::vector<size_t>& dim, std::vector<std::pair<size_t,size_t>>& roi);

	/**
	 * @brief Directional step, this will not step outside the region of 
	 * interest. Useful for kernels (maybe)
	 *
	 * @param dd	dimension to step in
	 * @param dist	distance to step (may be negative)
	 *
	 * @return new linear index
	 */
	size_t step(size_t dim, int64_t dist = 1);


	/**
	 * @brief Are we at the end in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the tail end of the particular dimension
	 */
	bool end(size_t dim);
	
	/**
	 * @brief Are we at the begin in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the start of the particular dimension
	 */
	bool begin(size_t dim);

	/**
	 * @brief Postfix iterator. Iterates in the order dictatored by the dimension
	 * order passsed during construction or by setOrder
	 *
	 * @param int	unused
	 *
	 * @return 	old value of linear position
	 */
	size_t operator++(int);
	

	/**
	 * @brief Prefix iterator. Iterates in the order dictatored by the dimension
	 * order passsed during construction or by setOrder
	 *
	 * @return 	new value of linear position
	 */
	size_t operator++();
	
	/**
	 * @brief Postfix negative  iterator. Iterates in the order dictatored by
	 * the dimension order passsed during construction or by setOrder
	 *
	 * @return 	old value of linear position
	 */
	size_t operator--(int);
	
	/**
	 * @brief Prefix negative  iterator. Iterates in the order dictatored by
	 * the dimension order passsed during construction or by setOrder
	 *
	 * @return 	new value of linear position
	 */
	size_t operator--();

	/**
	 * @brief dereference operator. Returns the linear position in the array 
	 * given the n-dimensional position.
	 *
	 * @return 
	 */
	size_t operator*()
	{
		return m_linpos;
	};

	/**
	 * @brief Get both ND position and linear position
	 *
	 * @param ndpos	Output, ND position
	 *
	 * @return linear position
	 */
	size_t getPos(std::vector<size_t>& ndpos)
	{
		ndpos.assign(m_pos.begin(), m_pos.end());
		return m_linpos;
	};

	/**
	 * @brief Are we at the begining of iteration?
	 *
	 * @return true if we are at the begining
	 */
	bool isBegin()
	{
		return m_linpos==m_linfirst;
	}

	/**
	 * @brief Are we at the end of iteration? Note that this will be 1 past the
	 * end, as typically is done in c++
	 *
	 * @return true if we are at the end
	 */
	bool isEnd()
	{
		return m_end;
	}

	/**
	 * @brief Are we at the begining of iteration?
	 *
	 * @return true if we are at the begining
	 */
	void setBegin()
	{
		for(size_t ii=0; ii<m_sizes.size(); ii++)
			m_pos[ii] = m_roi[ii].first;
		m_linpos = m_linfirst;
		m_end = false;
	}

	/**
	 * @brief Jump to the end of iteration.
	 *
	 * @return 
	 */
	void setEnd()
	{
		for(size_t ii=0; ii<m_sizes.size(); ii++)
			m_pos[ii] = m_roi[ii].second;
		m_linpos = m_linlast;
		m_end = true;
	}

	/**
	 * @brief Updates dimensions of target nd array
	 *
	 * @param dim	size of nd array, number of dimesions given by dim.size()
	 */
	void updateDim(std::vector<size_t>& dim);

	/**
	 * @brief Sets the region of interest. During iteration or any motion the
	 * position will not move outside the specified range
	 *
	 * @param roi	pair of [min,max] values in the desired hypercube
	 */
	void setROI(std::vector<std::pair<size_t, size_t>>& roi);

	/**
	 * @brief Sets the order of iteration from ++/-- operators
	 *
	 * @param order	vector of priorities, with first element being the fastest
	 * iteration and last the slowest. All other dimensions not used will be 
	 * slower than the last
	 */
	void setOrder(std::list<size_t>& order);


	/**
	 * @brief Jump to the given position
	 *
	 * @param newpos	location to move to
	 */
	void setPos(std::vector<size_t>& newpos);


private:

	size_t m_linpos;
	size_t m_linfirst;
	size_t m_linlast;
	bool m_end;
	std::vector<size_t> m_order;
	std::vector<size_t> m_pos;
	std::vector<std::pair<size_t,size_t>> m_roi;

	// these might benefit from being constant
	std::vector<size_t> m_sizes;
	std::vector<size_t> m_strides;
	size_t m_total;

	void updateLinRange();
};

/**
 * @brief Default Constructor, max a length 1, dimension 1 slicer
 */
Slicer::Slicer() 
{ 
	std::vector<size_t> tmp(1,1);
	updateDim(tmp);
};

/**
 * @brief Full Featured Constructor
 *
 * @param dim	size of ND array
 * @param order	order of iteration during ++, this doesn't affect step()
 * @param roi	min/max, roi is pair<size_t,size_t> = [min,max] 
 */
Slicer::Slicer(std::vector<size_t>& dim, std::list<size_t>& order,
		std::vector<std::pair<size_t,size_t>>& roi)
{
	updateDim(dim);
	setOrder(order);
	setROI(roi);
};

/**
 * @brief Simple (no ROI, no order) Constructor
 *
 * @param dim	size of ND array
 */
Slicer::Slicer(std::vector<size_t>& dim) 
{
	updateDim(dim);
};

/**
 * @brief Constructor that takes a dimension and order of ++/-- iteration
 *
 * @param dim	size of ND array
 * @param order	iteration direction, steps will be fastest in the direction
 * 				of order[0] and slowest in order.back()
 */
Slicer::Slicer(std::vector<size_t>& dim, std::list<size_t>& order)
{
	updateDim(dim);
	setOrder(order);
};

/**
 * @brief Constructor that takes a dimension and region of interest, which
 * is defined as min,max (inclusive)
 *
 * @param dim	size of ND array
 * @param roi	min/max, roi is pair<size_t,size_t> = [min,max] 
 */
Slicer::Slicer(std::vector<size_t>& dim, std::vector<std::pair<size_t,size_t>>& roi)
{
	updateDim(dim);
	setROI(roi);
};

/**
 * @brief Directional step, this will not step outside the region of 
 * interest. Useful for kernels (maybe)
 *
 * @param dd	dimension to step in
 * @param dist	distance to step (may be negative)
 *
 * @return new linear index
 */
size_t Slicer::step(size_t dim, int64_t dist)
{
	int64_t clamped = std::max<int64_t>(m_roi[dim].first, 
			std::min<int64_t>(m_roi[dim].second, (int64_t)m_pos[dim]+dist));
	m_linpos += (clamped-m_pos[dim])*m_strides[dim];
	m_pos[dim] = clamped;

	return m_linpos;
}

/**
 * @brief Are we at the end in a particular dimension
 *
 * @param dim	dimension to check
 *
 * @return whether we are at the tail end of the particular dimension
 */
bool Slicer::end(size_t dim)
{
	return m_pos[dim] == m_roi[dim].second;
}

/**
 * @brief Are we at the begin in a particular dimension
 *
 * @param dim	dimension to check
 *
 * @return whether we are at the start of the particular dimension
 */
bool Slicer::begin(size_t dim)
{
	return m_pos[dim] == m_roi[dim].first;
}


/**
 * @brief Postfix iterator. Iterates in the order dictatored by the dimension
 * order passsed during construction or by setOrder
 *
 * @param int	unused
 *
 * @return 	old value of linear position
 */
size_t Slicer::operator++(int)
{
	if(isEnd())
		return m_linpos;

	size_t ret = m_linpos;
	for(size_t ii=0; ii<m_order.size(); ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] < m_roi[dd].second) {
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			break;
		} else if(ii != m_order.size()-1){
			// highest dimension doesn't roll over
			// reset dimension
			m_linpos -= (m_pos[dd]-m_roi[dd].first)*m_strides[dd];
			m_pos[dd] = m_roi[dd].first;
		} else {
			// we are willing to go 1 past the last
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			m_end = true;
		}
	}

	return ret;
}

/**
 * @brief Prefix iterator. Iterates in the order dictatored by the dimension
 * order passsed during construction or by setOrder
 *
 * @return 	new value of linear position
 */
size_t Slicer::operator++() 
{
	if(isEnd())
		return m_linpos;

	for(size_t ii=0; ii<m_order.size(); ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] < m_roi[dd].second) {
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			break;
		} else if(ii != m_order.size()-1){
			// rool over (unles we are the last dimension)
			m_linpos -= (m_pos[dd]-m_roi[dd].first)*m_strides[dd];
			m_pos[dd] = m_roi[dd].first;
		} else {
			// we are willing to go 1 past the last
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			m_end = true;
		}
	}

	return m_linpos;
}

/**
 * @brief Postfix negative  iterator. Iterates in the order dictatored by
 * the dimension order passsed during construction or by setOrder
 *
 * @return 	new value of linear position
 */
size_t Slicer::operator--(int)
{
	if(isBegin())
		return m_linpos;

	m_end = false;
	size_t ret = m_linpos;
	for(size_t ii=0; ii<m_order.size(); ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] != m_roi[dd].first) {
			m_pos[dd]--;
			m_linpos -= m_strides[dd];
			break;
		} else if(ii != m_order.size()-1) {
			// jump forward in dd, (will pull back in next)
			m_linpos += m_roi[dd].second*m_strides[dd];
			m_pos[dd] = m_roi[dd].second;
		}
	}

	return ret;
};

/**
 * @brief Prefix negative  iterator. Iterates in the order dictatored by
 * the dimension order passsed during construction or by setOrder
 *
 * @return 	new value of linear position
 */
size_t Slicer::operator--() 
{
	if(isBegin())
		return m_linpos;

	m_end = false;
	for(size_t ii=0; ii<m_order.size(); ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] != m_roi[dd].first) {
			m_pos[dd]--;
			m_linpos -= m_strides[dd];
			break;
		} else if(ii != m_order.size()-1) {
			// jump forward in dd, (will pull back in next)
			m_linpos += m_roi[dd].second*m_strides[dd];
			m_pos[dd] = m_roi[dd].second;
		}
	}

	return m_linpos;
};

void Slicer::updateLinRange()
{
	m_total = 1;
	for(size_t ii=0; ii<m_sizes.size(); ii++)
		m_total *= m_sizes[ii];
	
	// all the dimensions should be at lower bound except lowest priority
	m_linfirst = 0;
	m_linlast = 0;
	for(size_t ii=0; ii<m_order.size(); ii++) {
		m_linfirst += m_strides[ii]*m_roi[ii].first;

		if(ii == m_order.size()-1) {
			m_linlast += m_strides[ii]*m_roi[ii].second;
		} else {
			m_linlast += m_strides[ii]*m_roi[ii].first;
		}
	}
};

/**
 * @brief Updates dimensions of target nd array
 *
 * @param dim	size of nd array, number of dimesions given by dim.size()
 */
void Slicer::updateDim(std::vector<size_t>& dim)
{
	size_t ndim = dim.size();
	assert(ndim > 0);

	m_roi.resize(dim.size());
	m_sizes.assign(dim.begin(), dim.end());
	m_order.resize(ndim);
	m_pos.resize(ndim);
	m_strides.resize(ndim);

	// reset position
	std::fill(m_pos.begin(), m_pos.end(), 0);
	m_linpos = 0;

	// reset ROI
	for(size_t ii=0; ii<ndim; ii++) {
		m_roi[ii].first = 0;
		m_roi[ii].second = m_sizes[ii]-1;
	};

	// reset default order
	for(size_t ii=0 ; ii<ndim ; ii++)
		m_order[ii] = m_order[ndim-1-ii];


	// set up strides
	m_strides[ndim-1] = 1;
	for(int64_t ii=(int64_t)ndim-2; ii>=0; ii--) {
		m_strides[ii] = m_strides[ii+1]*dim[ii+1];
	}

};

/**
 * @brief Sets the region of interest. During iteration or any motion the
 * position will not move outside the specified range. Invalidates position.
 *
 * @param roi	pair of [min,max] values in the desired hypercube
 */
void Slicer::setROI(std::vector<std::pair<size_t, size_t>>& roi)
{
	for(size_t ii=0; ii<m_sizes.size(); ii++) {
		if(ii < roi.size()) {
			// clamp, to be <= 0...sizes[ii]-1
			m_roi[ii].first = std::min(roi[ii].first, m_sizes[ii]-1);
			m_roi[ii].second = std::min(roi[ii].second, m_sizes[ii]-1);
		} else {
			// no specification, just make it all
			m_roi[ii].first = 0;
			m_roi[ii].second= m_sizes[ii]-1;
		}
	}

	updateLinRange();
	setBegin();
}

/**
 * @brief Sets the order of iteration from ++/-- operators. Invalidates
 * position, because the location of the last pixel changes.
 *
 * @param order	vector of priorities, with first element being the fastest
 * iteration and last the slowest. All other dimensions not used will be 
 * slower than the last
 */
void Slicer::setOrder(std::list<size_t>& order)
{
	size_t ndim = m_sizes.size();
	m_order.clear();

	// need to ensure that all dimensions get covered
	std::list<size_t> avail; 
	for(size_t ii=0 ; ii<ndim ; ii++)
		avail.push_front(ii);

	// add dimensions to internal order, but make sure there are 
	// no repeats
	for(auto ito=order.begin(); ito != order.end(); ito++) {

		// determine whether the given is available still
		auto it = std::find(avail.begin(), avail.end(), *ito);

		// should be available, although technically we could handle it, it
		// seems like a repeat would be a logic error
		assert(it != avail.end());
		if(it != avail.end()) {
			m_order.push_back(*it);
			avail.erase(it);
		}
	}

	// add any remaining dimensions to the order
	for(auto it=avail.begin(); it != avail.end(); ++it) 
		m_order.push_back(*it);

	updateLinRange();
	setBegin();
};

/**
 * @brief Jump to the given position
 *
 * @param newpos	location to move to
 */
void Slicer::setPos(std::vector<size_t>& newpos)
{
	m_linpos = 0;
	size_t ii=0;

	// copy the dimensions 
	for(;  ii<newpos.size() && ii<m_pos.size(); ii++) {
		m_pos[ii] = std::max(std::min(newpos[ii], m_roi[ii].second), 
				m_roi[ii].first);
		m_linpos += m_strides[ii]*m_pos[ii];
	}

	// set the unreferenced dimensions to 0
	for(;  ii<m_pos.size(); ii++) {
		m_pos[ii] = 0;
		m_linpos += m_strides[ii]*m_pos[ii];
	}
	m_end = false;
};

void linToIndex(size_t lpos, size_t& x, size_t& y, size_t& z, size_t& w,
		size_t sx, size_t sy, size_t sz, size_t sw)
{
	w = lpos%sw;
	lpos = lpos/sw;

	z = lpos%sz;
	lpos = lpos/sz;

	y = lpos%sy;
	lpos = lpos/sy;
	
	x = lpos%sx;
}

void indexToLin(size_t& lpos, size_t x, size_t y, size_t z, size_t w,
		size_t sx, size_t sy, size_t sz, size_t sw)
{
	(void)sx;

	lpos = 0;
	lpos = x*sy*sz*sw + y*sz*sw + z*sw + w;
}

int main()
{
	size_t X=2, Y=3, Z=4, W=5;
	std::vector<std::pair<size_t, size_t>> roi({{0,1},{0,1},{1,2},{1,3}});
	double array[X*Y*Z*W];
	size_t tx, ty, tz, tw;

	// canonical ordering
	size_t ii=0;
	for(size_t xx=0; xx<X; xx++) {
		for(size_t yy=0; yy<Y; yy++) {
			for(size_t zz=0; zz<Z; zz++) {
				for(size_t ww=0; ww<W; ww++) {
					size_t p;
					indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
					array[p] = ii++;

					linToIndex(p, tx,ty,tz,tw, X,Y,Z,W);
					if(tx != xx || ty != yy || tz != zz || tw != ww) {
						cerr << "Error in nd pos -> index -> nd pos conversion" 
							<< endl;
						return -1;
					}
				}
			}
		}
	}

	ii = 0;
	list<size_t> order({3,2,1,0});
	vector<size_t> pos;
	size_t p, xx, yy, zz, ww;

	std::vector<size_t> tdim({X,Y,Z,W});
	Slicer slicer(tdim);

	cerr << "Classic Ordering" << endl;
	slicer.setOrder(order);
	for(slicer.setBegin(); !slicer.isEnd(); slicer++, ii++) {
		
		size_t sp = slicer.getPos(pos);
		xx = pos[0]; yy = pos[1]; zz = pos[2]; ww = pos[3];

		indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
		if(p != sp) {
			cerr << "Disagreement on linear position" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}

		linToIndex(sp, tx,ty,tz,tw, X,Y,Z,W);

		if(tx != xx || ty != yy || tz != zz || tw != ww) {
			cerr << "Disagreement on ND position!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
		
		if(*slicer != array[sp]) {
			cerr << "Error, incorrect ordering!" << endl;
			return -1;
		}
	}
	cerr << "Done" << endl;
	
	cerr << endl << "Rotated 1" << endl;
	order.push_back(order.front());
	order.pop_front();

	slicer.setOrder(order);
	for(slicer.setBegin(); !slicer.isEnd(); slicer++, ii++) {
		
		size_t sp = slicer.getPos(pos);
		xx = pos[0]; yy = pos[1]; zz = pos[2]; ww = pos[3];
		cerr << xx << "," << yy << "," << zz << "," << ww << endl;

		indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
		if(p != sp) {
			cerr << "Disagreement on linear position" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}

		linToIndex(sp, tx,ty,tz,tw, X,Y,Z,W);

		if(tx != xx || ty != yy || tz != zz || tw != ww) {
			cerr << "Disagreement on ND position!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
		
		if(*slicer != array[sp]) {
			cerr << "Error, incorrect ordering!" << endl;
			return -1;
		}
	}
	cerr << endl;
	
	cerr << endl << "Rotated 2" << endl;
	order.push_back(order.front());
	order.pop_front();

	slicer.setOrder(order);
	for(slicer.setBegin(); !slicer.isEnd(); slicer++, ii++) {
		
		size_t sp = slicer.getPos(pos);
		xx = pos[0]; yy = pos[1]; zz = pos[2]; ww = pos[3];
		cerr << xx << "," << yy << "," << zz << "," << ww << endl;

		indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
		if(p != sp) {
			cerr << "Disagreement on linear position" << endl;
			return -1;
		}

		linToIndex(sp, tx,ty,tz,tw, X,Y,Z,W);

		if(tx != xx || ty != yy || tz != zz || tw != ww) {
			cerr << "Disagreement on ND position!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
		
		if(*slicer != array[sp]) {
			cerr << "Error, incorrect ordering!" << endl;
			return -1;
		}
	}
	cerr << endl;
	
	cerr << endl << "Rotated 3" << endl;
	order.push_back(order.front());
	order.pop_front();
	slicer.setOrder(order);
	for(slicer.setBegin(); !slicer.isEnd(); slicer++, ii++) {
		
		size_t sp = slicer.getPos(pos);
		xx = pos[0]; yy = pos[1]; zz = pos[2]; ww = pos[3];
		cerr << xx << "," << yy << "," << zz << "," << ww << endl;

		indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
		if(p != sp) {
			cerr << "Disagreement on linear position" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}

		linToIndex(sp, tx,ty,tz,tw, X,Y,Z,W);

		if(tx != xx || ty != yy || tz != zz || tw != ww) {
			cerr << "Disagreement on ND position!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
		
		if(*slicer != array[sp]) {
			cerr << "Error, incorrect ordering!" << endl;
			return -1;
		}
	}
	cerr << endl;

	// roi 
	cerr << endl << "Previous, With ROI" << endl;
	slicer.setROI(roi);
	for(slicer.setBegin(); !slicer.isEnd(); slicer++, ii++) {
		
		size_t sp = slicer.getPos(pos);
		xx = pos[0]; yy = pos[1]; zz = pos[2]; ww = pos[3];
		cerr << xx << "," << yy << "," << zz << "," << ww << endl;

		indexToLin(p, xx,yy,zz,ww, X,Y,Z,W);
		if(p != sp) {
			cerr << "Disagreement on linear position" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}

		linToIndex(sp, tx,ty,tz,tw, X,Y,Z,W);

		if(tx != xx || ty != yy || tz != zz || tw != ww) {
			cerr << "Disagreement on ND position!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
		
		if(*slicer != array[sp]) {
			cerr << "Error, incorrect ordering!" << endl;
			cerr << xx << "," << yy << "," << zz << "," << ww << endl;
			cerr << tx << "," << ty << "," << tz << "," << tw << endl;
			cerr << p << " vs " << sp << endl;
			return -1;
		}
	}
	cerr << endl;
}
