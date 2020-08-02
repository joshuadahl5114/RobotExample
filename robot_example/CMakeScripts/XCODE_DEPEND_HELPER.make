# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.robot_example.Debug:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/Debug/robot_example:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/Debug/robot_example


PostBuild.robot_example.Release:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/Release/robot_example:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/Release/robot_example


PostBuild.robot_example.MinSizeRel:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/MinSizeRel/robot_example:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/MinSizeRel/robot_example


PostBuild.robot_example.RelWithDebInfo:
/Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/RelWithDebInfo/robot_example:
	/bin/rm -f /Users/joshuadahl/Desktop/Tools/OpenGL\ Book\ Examples/chapter_4/robot_example/RelWithDebInfo/robot_example




# For each target create a dummy ruleso the target does not have to exist
