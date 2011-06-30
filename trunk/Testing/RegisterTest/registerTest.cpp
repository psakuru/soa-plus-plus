#include "../../ServiceOrientedArchitecture/Register/RegisterManager.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/SkeletonThreadPool/RegistrableSkeletonThreadPool/RegistrableSkeletonThreadPool.h"
#include "../../ServiceOrientedArchitecture/Service/Skeleton/PoolableCallableSkeleton/RegistrablePoolableCallableSkeletonWrapper/RegistrablePoolableCallableSkeletonWrapper.h"
#include "../../ServiceOrientedArchitecture/Register/Utilities/ExtensibleMap/MonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap/RRFIFOMonitoredExtensibleMap.h"

int main()
{
RegistrableObject* r =
new RegistrableSkeletonThreadPool
<
	RegistrablePoolableCallableSkeletonWrapper
	<
		RegisterManager
		<
			RRFIFOMonitoredExtensibleMap
		>
	>,
	1
>
("127.0.0.1", 4000, SOMAXCONN);
while(1){}
delete r;
return 0;
}
