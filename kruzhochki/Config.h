#ifndef KRUZHOCHKI_CONFIG_H
#define KRUZHOCHKI_CONFIG_H

#define KRUZ_DEBUG

#ifdef KRUZ_DEBUG
#include <iostream>
namespace kruz
{
#define kruzDebug(M) std::cout << "DEBUG(" << __FILE__ << ',' << __LINE__ << "):: " << M << std::endl
}
#else
namespace kruz
{
#define kruzDebug(M) ()
}
#endif // KRUZ_DEBUG

#endif // KRUZHOCHKI_CONFIG_H
