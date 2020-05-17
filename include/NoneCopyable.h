#ifndef INCLUDE_NONECOPYABLE_H_
#define INCLUDE_NONECOPYABLE_H_

namespace EventLoop
{

class NoneCopyable
{
public:
	NoneCopyable();

	~NoneCopyable();

private:
	NoneCopyable(const NoneCopyable &);
	NoneCopyable(const NoneCopyable &&);

	NoneCopyable &operator = (const NoneCopyable &);
	NoneCopyable &operator = (const NoneCopyable &&);
};

} /* namespace EventLoop */

#endif /* INCLUDE_NONECOPYABLE_H_ */
