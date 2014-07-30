
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

class SlicerBase
{
public:

//	/**
//	 * @brief Default Constructor, max a length 1, dimension 1 slicer
//	 */
//	SlicerBase();
//	
//	/**
//	 * @brief Full constructor, d indicates the length of dim, and roi1 roi2,
//	 * This MUST match the underlying dimensionality. d is an intentional 
//	 * redundancy. roi1 and roi2 indicate the bounding box. and order indicates the
//	 * order of iteration in terms of which dimensions are fastest
//	 *
//	 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
//	 * 					roi1 and roi2. 
//	 * @param dim		dimensions of the region, as in size
//	 * @param roi1		Region of interest to iterate over. Must be contained 
//	 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
//	 * 					Indicates range of indices: 
//	 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
//	 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
//	 * 					be either NULL or a array of length d, it must not be 
//	 * 					shorter!
//	 * @param roi2		See roi1
//	 * @param order		Order of dimensions to iterate over, so the first member
//	 * 					of order indicates which dimension you want to go the
//	 * 					fastest. Unspecified dimensions will be slower than 
//	 * 					members of order.
//	 * @param revorder	Reverse order, in which case the first element of order
//	 * 					will have the slowest iteration, and dimensions not
//	 * 					specified in order will be faster than those included.
//	 */
//	SlicerBase(size_t d, size_t* dim, size_t* roi1, size_t* roi2,
//			std::list<size_t>& order, bool revorder);
//	
//	/**
//	 * @brief Constructor, d indicates the length of dim, and roi1 roi2,
//	 * This MUST match the underlying dimensionality. d is an intentional 
//	 * redundancy. roi1 and roi2 indicate the bounding box.
//	 *
//	 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
//	 * 					roi1 and roi2. 
//	 * @param dim		dimensions of the region, as in size
//	 * @param roi1		Region of interest to iterate over. Must be contained 
//	 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
//	 * 					Indicates range of indices: 
//	 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
//	 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
//	 * 					be either NULL or a array of length d, it must not be 
//	 * 					shorter!
//	 * @param roi2		See roi1
//	 */
//	SlicerBase(size_t d, size_t* dim, size_t* roi1 = NULL, size_t* roi2 = NULL);

	/**
	 * @brief Directional step, this will not step outside the region of 
	 * interest. Useful for kernels (maybe)
	 *
	 * @param dd		dimension to step in
	 * @param dist		distance to step (may be negative)
	 * @param outside	if not null, then this will be set to to true if the 
	 * 					step would have taken use outside (and therefore wasn't
	 * 					performed).
	 *
	 * @return new linear index
	 */
	virtual size_t step(size_t dim, int64_t dist = 1, bool* outside = NULL) = 0;
	
	/**
	 * @brief 			Get linear index of a coordinate offset from the current
	 * 					position. 
	 *
	 * @param len		length of offset array, must match D
	 * @param dist		array of coordinates to offset by
	 * @param outside	if not null, then this will be set to to true if the 
	 * 					step would have taken use outside (and therefore wasn't
	 * 					performed).
	 *
	 * @return linear index
	 */
	virtual size_t offset(size_t len, int64_t * off, bool* outside = NULL) = 0;

	/**
	 * @brief Are we at the end in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the tail end of the particular dimension
	 */
	virtual bool isEnd(size_t dim) = 0;
	
	/**
	 * @brief Are we at the end of the iteration region of interest
	 *
	 * @return whether we are at the end of iteration
	 */
	virtual bool isEnd() = 0;
	
	/**
	 * @brief Are we at the begin in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the start of the particular dimension
	 */
	virtual bool isBegin(size_t dim) = 0;

	/**
	 * @brief Are we at the beginning
	 *
	 * @return whether we are at the start of iteration 
	 */
	virtual bool isBegin() = 0;

	/**
	 * @brief Postfix iterator. Iterates in the order dictatored by the dimension
	 * order passsed during construction or by setOrder
	 *
	 * @param int	unused
	 *
	 * @return 	old value of linear position
	 */
	virtual size_t operator++(int) = 0;
	
	/**
	 * @brief Prefix iterator. Iterates in the order dictatored by the dimension
	 * order passsed during construction or by setOrder
	 *
	 * @return 	new value of linear position
	 */
	virtual size_t operator++() = 0;
	
	/**
	 * @brief Postfix negative  iterator. Iterates in the order dictatored by
	 * the dimension order passsed during construction or by setOrder
	 *
	 * @return 	old value of linear position
	 */
	virtual size_t operator--(int) = 0;
	
	/**
	 * @brief Prefix negative  iterator. Iterates in the order dictatored by
	 * the dimension order passsed during construction or by setOrder
	 *
	 * @return 	new value of linear position
	 */
	virtual size_t operator--() = 0;

	/**
	 * @brief dereference operator. Returns the linear position in the array 
	 * given the n-dimensional position.
	 *
	 * @return 
	 */
	virtual size_t operator*() = 0;

	/**
	 * @brief Get both ND position and linear position
	 *
	 * @param ndpos	Output, ND position
	 *
	 * @return linear position
	 */
	virtual size_t getPos(std::vector<size_t>& ndpos) = 0;

	/**
	 * @brief Are we at the begining of iteration?
	 *
	 * @return true if we are at the begining
	 */
	virtual void goBegin() = 0;

	/**
	 * @brief Jump to the end of iteration.
	 *
	 * @return 
	 */
	virtual void goEnd() = 0;

	/**
	 * @brief Updates dimensions of target nd array
	 *
	 * @param len	length of dim array, must match template param D
	 * @param dim	new size to use
	 */
	virtual void updateDim(size_t len, size_t* dim) = 0;

	/**
	 * @brief Sets the region of interest. During iteration or any motion the
	 * position will not move outside the specified range
	 *
	 * @param roi	pair of [min,max] values in the desired hypercube
	 */
	virtual void setROI(size_t len, size_t* roi1, size_t* roi2) = 0;

	/**
	 * @brief Sets the order of iteration from ++/-- operators
	 *
	 * @param order	vector of priorities, with first element being the fastest
	 * iteration and last the slowest. All other dimensions not used will be 
	 * slower than the last
	 */
	virtual void setOrder(const std::list<size_t>& order, bool revorder = false) = 0;


	/**
	 * @brief Jump to the given position
	 *
	 * @param len		Length of newpos array must match D
	 * @param newpos	array of position
	 * @param outside	if no NULL, then this will be set true if the desired
	 * 					position mapped outside the ROI, in which case the 
	 * 					nearest point within the roi was used instead
	 */
	virtual void goPos(size_t len, size_t* newpos, bool* outside = NULL) = 0;

private:
};

/**
 * @brief This class is used to slice an image in along a dimension, and to 
 * step an arbitrary direction in an image. Order may be any size from 0 to the
 * number of dimensions. The first member of order will be the fastest moving,
 * and the last will be the slowest. Any not dimensions not included in the order
 * vector will be slower than the last member of order
 */
template <size_t D>
class Slicer : public virtual SlicerBase
{
public:

	/**
	 * @brief Default Constructor, max a length 1, dimension 1 slicer
	 */
	Slicer();
	
	/**
	 * @brief Full constructor, d indicates the length of dim, and roi1 roi2,
	 * This MUST match the underlying dimensionality. d is an intentional 
	 * redundancy. roi1 and roi2 indicate the bounding box. and order indicates the
	 * order of iteration in terms of which dimensions are fastest
	 *
	 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
	 * 					roi1 and roi2. 
	 * @param dim		dimensions of the region, as in size
	 * @param roi1		Region of interest to iterate over. Must be contained 
	 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
	 * 					Indicates range of indices: 
	 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
	 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
	 * 					be either NULL or a array of length d, it must not be 
	 * 					shorter!
	 * @param roi2		See roi1
	 * @param order		Order of dimensions to iterate over, so the first member
	 * 					of order indicates which dimension you want to go the
	 * 					fastest. Unspecified dimensions will be slower than 
	 * 					members of order.
	 * @param revorder	Reverse order, in which case the first element of order
	 * 					will have the slowest iteration, and dimensions not
	 * 					specified in order will be faster than those included.
	 */
	Slicer(size_t d, size_t* dim, size_t* roi1, size_t* roi2,
			std::list<size_t>& order, bool revorder);
	
	/**
	 * @brief Constructor, d indicates the length of dim, and roi1 roi2,
	 * This MUST match the underlying dimensionality. d is an intentional 
	 * redundancy. roi1 and roi2 indicate the bounding box.
	 *
	 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
	 * 					roi1 and roi2. 
	 * @param dim		dimensions of the region, as in size
	 * @param roi1		Region of interest to iterate over. Must be contained 
	 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
	 * 					Indicates range of indices: 
	 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
	 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
	 * 					be either NULL or a array of length d, it must not be 
	 * 					shorter!
	 * @param roi2		See roi1
	 */
	Slicer(size_t d, size_t* dim, size_t* roi1 = NULL, size_t* roi2 = NULL);

	/**
	 * @brief Directional step, this will not step outside the region of 
	 * interest. Useful for kernels (maybe)
	 *
	 * @param dd		dimension to step in
	 * @param dist		distance to step (may be negative)
	 * @param outside	if not null, then this will be set to to true if the 
	 * 					step would have taken use outside (and therefore wasn't
	 * 					performed).
	 *
	 * @return new linear index
	 */
	size_t step(size_t dim, int64_t dist = 1, bool* outside = NULL);
	
	/**
	 * @brief 			Get linear index of a coordinate offset from the current
	 * 					position. 
	 *
	 * @param len		length of offset array, must match D
	 * @param dist		array of coordinates to offset by
	 * @param outside	if not null, then this will be set to to true if the 
	 * 					step would have taken use outside (and therefore wasn't
	 * 					performed).
	 *
	 * @return linear index
	 */
	size_t offset(size_t len, int64_t * off, bool* outside = NULL);

	/**
	 * @brief Are we at the end in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the tail end of the particular dimension
	 */
	bool isEnd(size_t dim);
	
	/**
	 * @brief Are we at the end of the iteration region of interest
	 *
	 * @return whether we are at the end of iteration
	 */
	bool isEnd();
	
	/**
	 * @brief Are we at the begin in a particular dimension
	 *
	 * @param dim	dimension to check
	 *
	 * @return whether we are at the start of the particular dimension
	 */
	bool isBegin(size_t dim);

	/**
	 * @brief Are we at the beginning
	 *
	 * @return whether we are at the start of iteration 
	 */
	bool isBegin();

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
	size_t operator*();

	/**
	 * @brief Get both ND position and linear position
	 *
	 * @param ndpos	Output, ND position
	 *
	 * @return linear position
	 */
	size_t getPos(std::vector<size_t>& ndpos);

	/**
	 * @brief Are we at the begining of iteration?
	 *
	 * @return true if we are at the begining
	 */
	void goBegin();

	/**
	 * @brief Jump to the end of iteration.
	 *
	 * @return 
	 */
	void goEnd();

	/**
	 * @brief Updates dimensions of target nd array
	 *
	 * @param len	length of dim array, must match template param D
	 * @param dim	new size to use
	 */
	void updateDim(size_t len, size_t* dim);

	/**
	 * @brief Sets the region of interest. During iteration or any motion the
	 * position will not move outside the specified range
	 *
	 * @param roi	pair of [min,max] values in the desired hypercube
	 */
	void setROI(size_t len, size_t* roi1, size_t* roi2);

	/**
	 * @brief Sets the order of iteration from ++/-- operators
	 *
	 * @param order	vector of priorities, with first element being the fastest
	 * iteration and last the slowest. All other dimensions not used will be 
	 * slower than the last
	 * @param revorder reverse the final order meaning the first variable in 
	 * order will be slowest to iterate.
	 */
	void setOrder(const std::list<size_t>& order, bool revorder = false);

	/**
	 * @brief Jump to the given position
	 *
	 * @param len		Length of newpos array must match D
	 * @param newpos	array of position
	 * @param outside	if no NULL, then this will be set true if the desired
	 * 					position mapped outside the ROI, in which case the 
	 * 					nearest point within the roi was used instead
	 */
	void goPos(size_t len, size_t* newpos, bool* outside = NULL);


	const size_t ndim;

private:

	size_t m_linpos;
	size_t m_linfirst;
	size_t m_linlast;
	bool m_end;
	size_t m_order[D];
	size_t m_pos[D];
	size_t m_roi[D][2];

	// these might benefit from being constant
	size_t m_sizes[D];
	size_t m_strides[D];
	size_t m_total;

	void updateLinRange();
};

/**
 * @brief Default Constructor, max a length 1, dimension 1 slicer
 */
template <size_t D>
Slicer<D>::Slicer() 
{ 
	size_t tmp[D];
	std::fill(tmp, tmp+D, 0);

	updateDim(D, tmp);
};
	
/**
 * @brief Full constructor, d indicates the length of dim, and roi1 roi2,
 * This MUST match the underlying dimensionality. d is an intentional 
 * redundancy. roi1 and roi2 indicate the bounding box. and order indicates the
 * order of iteration in terms of which dimensions are fastest
 *
 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
 * 					roi1 and roi2. 
 * @param dim		dimensions of the region, as in size
 * @param roi1		Region of interest to iterate over. Must be contained 
 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
 * 					Indicates range of indices: 
 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
 * 					be either NULL or a array of length d, it must not be 
 * 					shorter!
 * @param roi2		See roi1
 * @param order		Order of dimensions to iterate over, so the first member
 * 					of order indicates which dimension you want to go the
 * 					fastest. Unspecified dimensions will be slower than 
 * 					members of order.
 * @param revorder	Reverse order, in which case the first element of order
 * 					will have the slowest iteration, and dimensions not
 * 					specified in order will be faster than those included.
 */
template <size_t D>
Slicer<D>::Slicer(size_t d, size_t* dim, size_t* roi1, size_t* roi2,
		std::list<size_t>& order, bool revorder) : ndim(D)
{
	assert(dim);
	updateDim(d, dim);
	setROI(d, roi1, roi2);
	setOrder(order, revorder);
}

/**
 * @brief Constructor, d indicates the length of dim, and roi1 roi2,
 * This MUST match the underlying dimensionality. d is an intentional 
 * redundancy. roi1 and roi2 indicate the bounding box.
 *
 * @param d			length of dim[] and (if roi1,roi2 != NULL) the length of 
 * 					roi1 and roi2. 
 * @param dim		dimensions of the region, as in size
 * @param roi1		Region of interest to iterate over. Must be contained 
 * 					in dim (ie, 0 <= min(roi1[dd],roi2[dd]) < dim[0]).
 * 					Indicates range of indices: 
 * 					[min(roi1[dd],roi2[dd]), max(roi1[dd],roi2[22])] will be 
 * 					used. ROI IS INCLUSIVE. Also note that this pointer may 
 * 					be either NULL or a array of length d, it must not be 
 * 					shorter!
 * @param roi2		See roi1
 */
template <size_t D>
Slicer<D>::Slicer(size_t d, size_t* dim, size_t* roi1, size_t* roi2) : ndim(D)
{
	assert(dim);
	updateDim(d, dim);
	setROI(d, roi1, roi2);
}

/**
 * @brief Directional step, this will not step outside the region of 
 * interest. Useful for kernels (maybe)
 *
 * @param dd		dimension to step in
 * @param dist		distance to step (may be negative)
 * @param outside	if not null, then this will be set to to true if the 
 * 					step would have taken use outside (and therefore wasn't
 * 					performed).
 *
 * @return new linear index
 */
template <size_t D>
size_t Slicer<D>::step(size_t dim, int64_t dist, bool* outside)
{
	if(dim >= D) throw std::logic_error("Invalid dimension passed to Slicer::Step");

	int64_t clamped = std::max<int64_t>(m_roi[dim][0], 
			std::min<int64_t>(m_roi[dim][1], (int64_t)m_pos[dim]+dist));
	m_linpos += (clamped-m_pos[dim])*m_strides[dim];

	if(outside) {
		if(((int64_t)m_pos[dim])+dist != clamped)
			*outside = true;
		else
			*outside = false;
	}
	m_pos[dim] = clamped;

	return m_linpos;
}


/**
 * @brief Directional step, this will not step outside the region of 
 * interest. Useful for kernels (maybe)
 *
 * @param len		length of offset array, must match D
 * @param dist		array of coordinates to offset by
 * @param outside	if not null, then this will be set to to true if the 
 * 					step would have taken use outside (and therefore wasn't
 * 					performed).
 *
 * @return linear index
 */
template <size_t D>
size_t Slicer<D>::offset(size_t len, int64_t* off, bool* outside)
{
	if(len > D) 
		throw std::out_of_range("Invalid dimension passed to Slicer::Step");
		
	if(outside) {
		*outside = false;
	}

	int64_t clamped;
	size_t linpos = m_linpos;
	for(size_t ii=0; ii<D; ii++) {
		clamped = std::max<int64_t>(m_roi[ii][0], 
				std::min<int64_t>(m_roi[ii][1], m_pos[ii]+off[ii]));
		linpos += (clamped-m_pos[ii])*m_strides[ii];
		
		if(outside && ((int64_t)m_pos[ii])+off[ii] == clamped)
			*outside = true;
	}

	return m_linpos;
}


/**
 * @brief Postfix iterator. Iterates in the order dictatored by the dimension
 * order passsed during construction or by setOrder
 *
 * @param int	unused
 *
 * @return 	old value of linear position
 */
template <size_t D>
size_t Slicer<D>::operator++(int)
{
	if(isEnd())
		return m_linpos;

	size_t ret = m_linpos;
	for(size_t ii=0; ii<D; ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] < m_roi[dd][1]) {
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			break;
		} else if(ii != D-1){
			// highest dimension doesn't roll over
			// reset dimension
			m_linpos -= (m_pos[dd]-m_roi[dd][0])*m_strides[dd];
			m_pos[dd] = m_roi[dd][0];
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
template <size_t D>
size_t Slicer<D>::operator++() 
{
	if(isEnd())
		return m_linpos;

	for(size_t ii=0; ii<D; ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] < m_roi[dd][1]) {
			m_pos[dd]++;
			m_linpos += m_strides[dd];
			break;
		} else if(ii != D-1){
			// rool over (unles we are the last dimension)
			m_linpos -= (m_pos[dd]-m_roi[dd][0])*m_strides[dd];
			m_pos[dd] = m_roi[dd][0];
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
template <size_t D>
size_t Slicer<D>::operator--(int)
{
	if(isBegin())
		return m_linpos;

	m_end = false;
	size_t ret = m_linpos;
	for(size_t ii=0; ii<D ; ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] != m_roi[dd][0]) {
			m_pos[dd]--;
			m_linpos -= m_strides[dd];
			break;
		} else if(ii != D-1) {
			// jump forward in dd, (will pull back in next)
			m_linpos += m_roi[dd][1]*m_strides[dd];
			m_pos[dd] = m_roi[dd][1];
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
template <size_t D>
size_t Slicer<D>::operator--() 
{
	if(isBegin())
		return m_linpos;

	m_end = false;
	for(size_t ii=0; ii<D; ii++){
		size_t dd = m_order[ii];
		if(m_pos[dd] != m_roi[dd][0]) {
			m_pos[dd]--;
			m_linpos -= m_strides[dd];
			break;
		} else if(ii != D-1) {
			// jump forward in dd, (will pull back in next)
			m_linpos += m_roi[dd][1]*m_strides[dd];
			m_pos[dd] = m_roi[dd][1];
		}
	}

	return m_linpos;
};

/**
 * @brief dereference operator. Returns the linear position in the array 
 * given the n-dimensional position.
 *
 * @return 
 */
template <size_t D>
size_t Slicer<D>::operator*()
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
template <size_t D>
size_t Slicer<D>::getPos(std::vector<size_t>& ndpos)
{
	ndpos.assign(m_pos, m_pos+D);
	return m_linpos;
};

/**
 * @brief Are we at the beginning
 *
 * @return whether we are at the start of iteration 
 */
template <size_t D>
bool Slicer<D>::isBegin()
{
	return m_linpos==m_linfirst;
}

/**
 * @brief Are we at the end of the iteration region of interest
 *
 * @return whether we are at the end of iteration
 */
template <size_t D>
bool Slicer<D>::isEnd()
{
	return m_end;
}

/**
 * @brief Are we at the end in a particular dimension
 *
 * @param dim	dimension to check
 *
 * @return whether we are at the tail end of the particular dimension
 */
template <size_t D>
bool Slicer<D>::isEnd(size_t dim)
{
	return m_pos[dim] == m_roi[dim][1];
}

/**
 * @brief Are we at the begin in a particular dimension
 *
 * @param dim	dimension to check
 *
 * @return whether we are at the start of the particular dimension
 */
template <size_t D>
bool Slicer<D>::isBegin(size_t dim)
{
	if(dim >= D) throw logic_error("Invalid dimension passed to Slicer::isBegin");
	return m_pos[dim] == m_roi[dim][0];
}

/**
 * @brief Are we at the begining of iteration?
 *
 * @return true if we are at the begining
 */
	template <size_t D>
void Slicer<D>::goBegin()
{
	for(size_t ii=0; ii<D; ii++)
		m_pos[ii] = m_roi[ii][0];
	m_linpos = m_linfirst;
	m_end = false;
}

/**
 * @brief Jump to the end of iteration.
 *
 * @return 
 */
template <size_t D>
void Slicer<D>::goEnd()
{
	for(size_t ii=0; ii<D; ii++)
		m_pos[ii] = m_roi[ii][1];
	m_linpos = m_linlast;
	m_end = true;
}


/**
 * @brief Computes the range of linear index values so that we can determine 
 * if we are at the end of iteration or not. Just plumbing.
 *
 * @tparam D
 */
template <size_t D>
void Slicer<D>::updateLinRange()
{
	m_total = 1;
	for(size_t ii=0; ii<D; ii++)
		m_total *= m_sizes[ii];

	// all the dimensions should be at lower bound except lowest priority
	m_linfirst = 0;
	m_linlast = 0;
	for(size_t ii=0; ii<D; ii++) {
		m_linfirst += m_strides[ii]*m_roi[ii][0];

		if(ii == D-1) {
			m_linlast += m_strides[ii]*m_roi[ii][1];
		} else {
			m_linlast += m_strides[ii]*m_roi[ii][0];
		}
	}
};

/**
 * @brief Updates dimensions of target nd array
 *
 * @param len	length of dim array, must match template param D
 * @param dim	new size to use
 */
template <size_t D>
void Slicer<D>::updateDim(size_t len, size_t* dim)
{
	if(len != D) 
		throw std::out_of_range("Incorrect dimension provided to updateDim");

	for(size_t ii=0; ii<D; ii++)
		m_sizes[ii] = dim[ii];

	// reset position
	std::fill(m_pos, m_pos+D, 0);
	m_linpos = 0;

	// reset ROI
	for(size_t ii=0; ii<D; ii++) {
		m_roi[ii][0] = 0;
		m_roi[ii][1] = m_sizes[ii]-1;
	};

	// reset default order
	for(size_t ii=0 ; ii<D; ii++)
		m_order[ii] = D-1-ii;

	// set up strides
	m_strides[D-1] = 1;
	for(int64_t ii=(int64_t)D-2; ii>=0; ii--) {
		m_strides[ii] = m_strides[ii+1]*dim[ii+1];
	}

	updateLinRange();
	goBegin();
};

/**
 * @brief Sets the region of interest. During iteration or any motion the
 * position will not move outside the specified range. Invalidates position.
 * Both roi1 and roi2 may be set to NULL to use the full array, otherwise
 * both roi1 and roi2 should be arrays of length 'len'
 *
 * @param len		Length of newpos array must match D
 * @param roi1		On corner of the bounding box
 * @param roi2		The other corner of the bounding box
 */
template <size_t D>
void Slicer<D>::setROI(size_t len, size_t* roi1, size_t* roi2)
{
	if(len != D) throw std::logic_error("Incorrect roi dimension in setROI");

	if(roi1 == NULL || roi2 == NULL) {
		for(size_t ii=0; ii<D ; ii++) {
			m_roi[ii][0] = 0;
			m_roi[ii][1] = m_sizes[ii]-1;
		}
	} else {
		for(size_t ii=0; ii<D ; ii++) {
			size_t low = std::min(m_sizes[ii]-1, std::min(roi1[ii], roi2[ii]));
			size_t high = std::min(m_sizes[ii]-1, std::max(roi1[ii], roi2[ii]));
			// clamp, to be <= 0...sizes[ii]-1
			m_roi[ii][0] = low;
			m_roi[ii][1] = high;
		}
	}

	updateLinRange();
	goBegin();
}

/**
 * @brief Sets the order of iteration from ++/-- operators. Invalidates
 * position, because the location of the last pixel changes.
 *
 * @param 	order	vector of priorities, with first element being the fastest
 * 			iteration and last the slowest. All other dimensions not used will 
 * 			be slower than the last
 * @param 	after order is computed reverse the order. This means that the 
 * 			input order list would start with the slowest dimension and other 
 * 			dimensions would be the fastest, in no particular order
 */
template <size_t D>
void Slicer<D>::setOrder(const std::list<size_t>& order, bool revorder)
{
	// need to ensure that all dimensions get covered
	std::list<size_t> avail; 
	for(size_t ii=0 ; ii<D; ii++)
		avail.push_back(ii);

	int64_t order_it = 0;

	// add dimensions to internal order, but make sure there are 
	// no repeats
	for(auto ito=order.begin(); ito != order.end(); ito++) {

		// determine whether the given is available still
		auto it = std::find(avail.begin(), avail.end(), *ito);

		if(it != avail.end()) {
			m_order[order_it++] = *it;
			avail.erase(it);
		} else {
			throw std::logic_error("Repeated dimensions provided to set order");
		}
	}

	// we would like the dimensions to be added so that steps are small, 
	// so in revorder case, add dimensions in decreasing order (since they will
	// be flipped), in normal case add in increasing order. 
	// so dimensions 0 3, 5 might be remaining, with order currently:
	// m_order = {1,4,2}, 
	// in the case of revorder we will add the remaining dimensions as
	// m_order = {1,4,2,5,3,0}, because once we flip it will be {0,3,5,2,4,1}
	if(revorder) {
		for(auto it=avail.rbegin(); it != avail.rend(); ++it) 
			m_order[order_it++] = *it;
		// reverse 6D, {0,5},{1,4},{2,3}
		// reverse 5D, {0,4},{1,3}
		for(size_t ii=0; ii<D/2; ii++) 
			std::swap(m_order[ii],m_order[D-1-ii]);
	} else {
		for(auto it=avail.begin(); it != avail.end(); ++it) 
			m_order[order_it++] = *it;
	}
	
	updateLinRange();
	goBegin();
};

/**
 * @brief Jump to the given position
 *
 * @param len		Length of newpos array must match D
 * @param newpos	array of position
 * @param outside	if no NULL, then this will be set true if the desired
 * 					position mapped outside the ROI, in which case the 
 * 					nearest point within the roi was used instead
 */
template <size_t D>
void Slicer<D>::goPos(size_t len, size_t* newpos, bool* outside)
{
	size_t clamped;
	m_linpos = 0;

	if(len  != D) {
		throw std::logic_error("Incorrect Size of index to goPos");
	}
				
	if(outside) 
		*outside = false;

	// copy the dimensions 
	for(size_t ii=0; ii<D; ii++) {
		clamped = std::max(std::min(newpos[ii], m_roi[ii][1]), m_roi[ii][0]);

		if(outside && clamped != newpos[ii])
			*outside = true;

		m_linpos += m_strides[ii]*m_pos[ii];
	}

	// end it outside and therefore not setable
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
	size_t roi[2][4] = {{0,0,1,1},{1,1,2,3}};
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

	size_t tdim[] = {X,Y,Z,W};
	Slicer<4> slicer(4, tdim);

	cerr << "Classic Ordering" << endl;
	slicer.setOrder(order);
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		
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
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		
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
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		
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
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		
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
	slicer.setROI(4, roi[0], roi[1]);
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		
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

	size_t ITERS = 1;
	size_t sum = 0;
	cerr << "Speed Test!" << endl;
	clock_t t = clock();
	for(size_t ii=0 ; ii < ITERS; ii++) {
		for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) 
			sum += *slicer;
	}
	t = clock() - t;
	cerr << "Large restart Runtime: " << t << " ( " << t/CLOCKS_PER_SEC << " ) seconds" << endl;
	

	size_t newdim[4] = {50, 50, 50, 50};
	t = clock();
	slicer.updateDim(4, newdim);
	ii = 0;
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		sum += *slicer;
		if(ii >= 50*50*50*50) {
			cerr << "Error should have finished!" << endl;
			return -1;
		}
	}
	t = clock() - t;
	cerr << "Large Area Runtime: " << t << " ( " << t/CLOCKS_PER_SEC << " ) seconds" << endl;
	
	bool outside;
	int64_t off[4] = {0,0,0,-1};
	size_t prev = 0;;
	ii = 0;
	t = clock();
	for(slicer.goBegin(); !slicer.isEnd(); slicer++, ii++) {
		sum += *slicer;
		size_t oprev = slicer.offset(4, off, &outside);
		if(!outside && oprev != prev ) {
			cerr << "Error in offset " << endl;
			return -1;
		}
		if(ii >= 50*50*50*50) {
			cerr << "Error should have finished!" << endl;
			return -1;
		}
		prev = *slicer;
	}
	cerr << "Offset Runtime: " << t << " ( " << t/CLOCKS_PER_SEC << " ) seconds" << endl;
}

