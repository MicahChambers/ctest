

class KdTree
{
public:

	/**
	 * @brief Constructs a k-dimensional tree, where each point also has 
	 * E additional values. medpoint must be length k+E, and should ideally
	 * be somewhere in the middle of the point cloud
	 *
	 * @param k
	 * @param E
	 * @param medpoint
	 */
	KdTree(size_t k, size_t E, const std::vector<double>& medpoint) :
		m_dim(k), m_extra(datasize)
	{
		if(median.size() != dim)
		Node
	};
	
	bool insert(const std::vector<double>& v)
	{
		if(v.size() != m_dim + m_extra) {
			return false;
		}

		// insertion
	};

	bool insert(const std::vector<double>& v)
	{
		if(v.size() != m_dim + m_extra) {
			return false;
		}

		// insertion
	};
	
	class Node
	{
	public:
		std::vector<double> data;

	private:
		Node* left;
		Node* right;
		KdTree* parent;
	};
private:
	Node* head;
};


int main()
{

}
