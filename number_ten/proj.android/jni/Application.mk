APP_STL := gnustl_static
# Release.
APP_CPPFLAGS := -frtti
# Debug. Need this in order to output CCLOG.
# APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1