
#pragma once

#include "IUserProfileService.h"
#include <memory>
#include <vector>

namespace xplatform {

class IKeyValueStorage;


class UserProfileServiceImpl : public IUserProfileService {
    typedef std::shared_ptr<IUserProfileServiceListener> UserProfileListenerPtr;

public:

	UserProfileServiceImpl(const std::shared_ptr<IKeyValueStorage> & keyValueStorage);
	virtual UserProfile updateUserProfile(const UserProfile & userProfile) override;
	virtual boost::optional<UserProfile> getUserProfile() override;
	virtual void removeUserProfile() override;
    virtual void addListener(const std::shared_ptr<IUserProfileServiceListener> & listener) override;
    virtual void removeListener(const std::shared_ptr<IUserProfileServiceListener> & listener) override;

private:
    
    bool isListenerRegistered(std::shared_ptr<IUserProfileServiceListener> listener);
    void notifyListenersProfileUpdated(const UserProfile &userProfile);
    void notifyListenersProfileRemoved();
    std::vector<UserProfileListenerPtr>::iterator findListener(UserProfileListenerPtr listener);

	std::shared_ptr<IKeyValueStorage> keyValueStorage;
    std::vector<UserProfileListenerPtr> listeners;

};

}

