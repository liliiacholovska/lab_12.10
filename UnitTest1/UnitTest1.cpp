#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.10/lab12.10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(AddSingleNode)
        {
            Node* root = nullptr;
            addNode(root, "50");
            Assert::IsNotNull(root); 
            Assert::AreEqual(string("50"), root->info); 
            destroyTree(root); 
        }

        TEST_METHOD(AddMultipleNodes)
        {
            Node* root = nullptr;
            addNode(root, "50");
            addNode(root, "30");
            addNode(root, "70");
            Assert::IsNotNull(root);
            Assert::AreEqual(string("50"), root->info); 
            Assert::IsNotNull(root->left); 
            Assert::IsNotNull(root->right); 
            Assert::AreEqual(string("30"), root->left->info); 
            Assert::AreEqual(string("70"), root->right->info);
            destroyTree(root); 
        }

        TEST_METHOD(FindExistingNode)
        {
            Node* root = nullptr;
            addNode(root, "50");
            addNode(root, "30");
            addNode(root, "70");
            Assert::IsTrue(findNode(root, "30")); 
            destroyTree(root); 
        }

        TEST_METHOD(FindNonExistingNode)
        {
            Node* root = nullptr;
            addNode(root, "50");
            Assert::IsFalse(findNode(root, "30")); 
            destroyTree(root); 
        }

        TEST_METHOD(DeleteLeafNode)
        {
            Node* root = nullptr;
            addNode(root, "50");
            addNode(root, "30");
            addNode(root, "70");
            bool deleted = deleteNode(root, "30"); 
            Assert::IsTrue(deleted); 
            Assert::IsNull(root->left); 
            destroyTree(root); 
        }
        TEST_METHOD(DeleteNodeWithOneChild)
        {
            Node* root = nullptr;
            addNode(root, "50");
            addNode(root, "70");
            addNode(root, "60");
            bool deleted = deleteNode(root, "70"); 
            Assert::IsTrue(deleted); 
            Assert::IsNotNull(root->right); 
            Assert::AreEqual(string("60"), root->right->info); 
            destroyTree(root);
        }
        TEST_METHOD(DeleteNodeWithTwoChildren)
        {
            Node* root = nullptr;
            addNode(root, "50");
            addNode(root, "30");
            addNode(root, "70");
            addNode(root, "60");
            addNode(root, "80");
            bool deleted = deleteNode(root, "70");
            Assert::IsTrue(deleted);
            Assert::IsNotNull(root->right); 
            Assert::AreEqual(string("80"), root->right->info); 
            Assert::IsNotNull(root->right->left);
            Assert::AreEqual(string("60"), root->right->left->info); 
            destroyTree(root); 
        }
	};
}
