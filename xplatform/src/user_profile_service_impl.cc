#include "user_profile_service_impl.h"
#include "IKeyValueStorage.h"
#include "IUserProfileServiceListener.h"

namespace xplatform {

    static std::string const kProfileKey = "profile";
    static std::string const kProfileFirstNameKey = kProfileKey + "." + "firstName";
    static std::string const kProfileLastNameKey = kProfileKey + "." + "lastName";
    
    std::shared_ptr<IUserProfileService> IUserProfileService::createUserProfileService(const std::shared_ptr<IKeyValueStorage> & keyValueStorage)
    {
        return std::make_shared<UserProfileServiceImpl>(keyValueStorage);
    }
    
    UserProfileServiceImpl::UserProfileServiceImpl(const std::shared_ptr<IKeyValueStorage> & keyValueStorage) : keyValueStorage(keyValueStorage)
    {
        
    }
    
    UserProfile UserProfileServiceImpl::updateUserProfile(const UserProfile & userProfile)
    {
        keyValueStorage->writeString(kProfileFirstNameKey, userProfile.firstName);
        keyValueStorage->writeString(kProfileLastNameKey, userProfile.lastName);
        
        notifyListenersProfileUpdated(*(getUserProfile()));
        return userProfile;
    }
    
    boost::optional<UserProfile> UserProfileServiceImpl::getUserProfile()
    {
        auto firstName = keyValueStorage->readString(kProfileFirstNameKey);
        //If we can't read a first name, we don't have a profile.
        if (firstName) {
            auto lastName = keyValueStorage->readString(kProfileLastNameKey);
            return UserProfile(*firstName, *lastName);
        }
        boost::optional<UserProfile> userProfile;
        return userProfile;
    }
    
    void UserProfileServiceImpl::removeUserProfile()
    {
        keyValueStorage->remove(kProfileFirstNameKey);
        keyValueStorage->remove(kProfileLastNameKey);
        
        notifyListenersProfileRemoved();
    }
    
    void UserProfileServiceImpl::addListener(const std::shared_ptr<IUserProfileServiceListener> & listener)
    {
        if (!isListenerRegistered(listener)) {
            listeners.push_back(listener);
        }
    }
    
    void UserProfileServiceImpl::removeListener(const std::shared_ptr<IUserProfileServiceListener> & listener)
    {
        auto it = findListener(listener);
        if (it != listeners.end()) {
            listeners.erase(it);
        }
    }
    
    //Private methods
    
    std::vector<UserProfileServiceImpl::UserProfileListenerPtr>::iterator UserProfileServiceImpl::findListener(UserProfileListenerPtr listener)
    {
        return std::find(listeners.begin(), listeners.end(), listener);
    }
    
    bool UserProfileServiceImpl::isListenerRegistered(std::shared_ptr<IUserProfileServiceListener> listener)
    {
        return findListener(listener) != listeners.end();
    }
    
    void UserProfileServiceImpl::notifyListenersProfileUpdated(const UserProfile &userProfile)
    {
        for (auto it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->userProfileUpdated(userProfile);
        }
    }
    
    void UserProfileServiceImpl::notifyListenersProfileRemoved()
    {
        for (auto it = listeners.begin(); it != listeners.end(); it++) {
            (*it)->userProfileRemoved();
        }
    }

}

