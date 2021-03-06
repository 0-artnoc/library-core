////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           Library/Core/FileSystem/Directory.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Directory.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_FileSystem_Directory, EqualToOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/")) == Directory::Path(Path::Parse("/"))) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory"))) ;

    }

    {

        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory/"))) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory2"))) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path2/to/file"))) ;

    }

    {

        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Undefined()) ;
        EXPECT_FALSE(Directory::Undefined() == Directory::Path(Path::Parse("/path/to/directory"))) ;
        EXPECT_FALSE(Directory::Undefined() == Directory::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, NotEqualToOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory/"))) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory2"))) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path2/to/file"))) ;

    }

    {

        EXPECT_FALSE(Directory::Path(Path::Parse("/")) != Directory::Path(Path::Parse("/"))) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory"))) ;

    }

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Undefined()) ;
        EXPECT_TRUE(Directory::Undefined() != Directory::Path(Path::Parse("/path/to/directory"))) ;
        EXPECT_TRUE(Directory::Undefined() != Directory::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, StreamOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        const Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << directory << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, IsDefined)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/")).isDefined()) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")).isDefined()) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory/")).isDefined()) ;

    }

    {

        EXPECT_FALSE(Directory::Undefined().isDefined()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, Exists)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/")).exists()) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr")).exists()) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/bin")).exists()) ;

    }

    {

        EXPECT_FALSE(Directory::Path(Path::Parse("/skf47hksdjf")).exists()) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr/sdfkjdfg")).exists()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().exists()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, IsEmpty)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/games")).isEmpty()) ;
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/games/")).isEmpty()) ;

    }

    {

        EXPECT_FALSE(Directory::Path(Path::Parse("/")).isEmpty()) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr")).isEmpty()) ;
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr/")).isEmpty()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().isEmpty()) ;
        EXPECT_ANY_THROW(Directory::Path(Path::Parse("/abc")).isEmpty()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, ContainsFileWithName)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        const Directory directory = Directory::Path(Path::Parse("/app/tools/development")) ;

        EXPECT_TRUE(directory.containsFileWithName("exec.sh")) ;
        EXPECT_TRUE(directory.containsFileWithName("start.sh")) ;

        EXPECT_FALSE(directory.containsFileWithName("docker")) ;
        EXPECT_FALSE(directory.containsFileWithName("helpers")) ;
        EXPECT_FALSE(directory.containsFileWithName("abc")) ;

    }

    {

        const Directory directory = Directory::Path(Path::Parse("/app/tools/development")) ;

        EXPECT_ANY_THROW(Directory::Undefined().containsFileWithName("abc")) ;
        EXPECT_ANY_THROW(directory.containsFileWithName("")) ;
        EXPECT_ANY_THROW(Directory::Undefined().containsFileWithName("abc")) ;

    }

}

// TEST (Library_Core_FileSystem_Directory, ContainsDirectoryWithName)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Core_FileSystem_Directory, GetName)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_EQ("/", Directory::Path(Path::Parse("/")).getName()) ;
        EXPECT_EQ("usr", Directory::Path(Path::Parse("/usr")).getName()) ;
        EXPECT_EQ("usr", Directory::Path(Path::Parse("/usr/")).getName()) ;
        EXPECT_EQ("games", Directory::Path(Path::Parse("/usr/games")).getName()) ;
        EXPECT_EQ("games", Directory::Path(Path::Parse("/usr/games/")).getName()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().getName()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, GetPath)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_EQ(Path::Parse("/"), Directory::Path(Path::Parse("/")).getPath()) ;
        EXPECT_EQ(Path::Parse("/usr"), Directory::Path(Path::Parse("/usr")).getPath()) ;
        EXPECT_EQ(Path::Parse("/usr/"), Directory::Path(Path::Parse("/usr/")).getPath()) ;
        EXPECT_EQ(Path::Parse("/usr/games"), Directory::Path(Path::Parse("/usr/games")).getPath()) ;
        EXPECT_EQ(Path::Parse("/usr/games/"), Directory::Path(Path::Parse("/usr/games/")).getPath()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().getPath()) ;

    }

}

// TEST (Library_Core_FileSystem_Directory, GetPermissions)
// {

//     using library::core::fs::PermissionSet ;
//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         const Path path = Path::Parse("/app/build") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RWX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/app/build/") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RWX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/boot") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/boot/") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RX(), directory.getPermissions()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().getPermissions()) ;
//         EXPECT_ANY_THROW(Directory::Path(Path::Parse("/abc")).getPermissions()) ;

//     }

// }

TEST (Library_Core_FileSystem_Directory, GetParentDirectory)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/build")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/build/")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/does-not-exist")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/does-not-exist/")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/does-not-exist/.")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app//does-not-exist")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app//does-not-exist/")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app//does-not-exist/.")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/")), Directory::Path(Path::Parse("/")).getParentDirectory()) ;
        EXPECT_EQ(Directory::Path(Path::Parse("/")), Directory::Path(Path::Parse("/app/build/..")).getParentDirectory()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().getParentDirectory()) ;

    }

}

// TEST (Library_Core_FileSystem_Directory, GetFiles)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().getFiles()) ;

//     }

// }

TEST (Library_Core_FileSystem_Directory, GetDirectories)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        const Directory directory = Directory::Path(Path::Parse("/app/tools/development")) ;

        const Array<Directory> subDirectories = directory.getDirectories() ;

        EXPECT_EQ(2, subDirectories.getSize()) ;

        const Array<String> subDirectoryNames = subDirectories.map<String>([] (const Directory& aDirectory) -> String { return aDirectory.getName() ; }) ;

        const Array<String> referenceSubDirectoryNames = {"docker", "helpers"} ;

        EXPECT_EQ(referenceSubDirectoryNames, subDirectoryNames) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().getDirectories()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, ToString)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_EQ("/app/build", Directory::Path(Path::Parse("/app/build")).toString()) ;
        EXPECT_EQ("/app/build/", Directory::Path(Path::Parse("/app/build/")).toString()) ;
        EXPECT_EQ("/app//does-not-exist", Directory::Path(Path::Parse("/app//does-not-exist")).toString()) ;
        EXPECT_EQ("/", Directory::Path(Path::Parse("/")).toString()) ;
        EXPECT_EQ("/app/build/..", Directory::Path(Path::Parse("/app/build/..")).toString()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().toString()) ;

    }

}

// TEST (Library_Core_FileSystem_Directory, RenameTo)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().renameTo()) ;

//     }

// }

// TEST (Library_Core_FileSystem_Directory, CopyToDirectory)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().copyToDirectory()) ;

//     }

// }

// TEST (Library_Core_FileSystem_Directory, MoveToDirectory)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().moveToDirectory()) ;

//     }

// }

TEST (Library_Core_FileSystem_Directory, Create)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        Directory directory = Directory::Path(Path::Parse("/tmp/library-core-filesystem-directory-create")) ;

        EXPECT_FALSE(directory.exists()) ;

        directory.create() ;

        EXPECT_TRUE(directory.exists()) ;

        EXPECT_ANY_THROW(directory.create()) ;

        directory.remove() ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().create()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, Remove)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        Directory directory = Directory::Path(Path::Parse("/tmp/library-core-filesystem-directory-remove")) ;

        directory.create() ;

        EXPECT_TRUE(directory.exists()) ;

        directory.remove() ;

        EXPECT_FALSE(directory.exists()) ;

        EXPECT_ANY_THROW(directory.remove()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Undefined().remove()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, Undefined)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_NO_THROW(Directory::Undefined()) ;
        EXPECT_FALSE(Directory::Undefined().isDefined()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, Root)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        EXPECT_NO_THROW(Directory::Root()) ;
        EXPECT_TRUE(Directory::Root().isDefined()) ;
        EXPECT_EQ(Path::Parse("/"), Directory::Root().getPath()) ;

    }

}

TEST (Library_Core_FileSystem_Directory, Path)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    {

        const Path path = Path::Parse("/path/to/directory") ;

        EXPECT_TRUE(Directory::Path(path).isDefined()) ;

        EXPECT_EQ(path, Directory::Path(path).getPath()) ;

    }

    {

        const Path path = Path::Parse("/path/to/directory/") ;

        EXPECT_TRUE(Directory::Path(path).isDefined()) ;

        EXPECT_EQ(path, Directory::Path(path).getPath()) ;

    }

    {

        EXPECT_ANY_THROW(Directory::Path(Path::Parse(""))) ;
        EXPECT_ANY_THROW(Directory::Path(Path::Undefined())) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
