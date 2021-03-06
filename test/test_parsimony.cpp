#include "gtest/gtest.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include <Bpp/Seq/Container/SiteContainer.h>
#include <Bpp/Seq/Container/SiteContainerTools.h>
#include <Bpp/Seq/Container/VectorSiteContainer.h>
#include <Bpp/Seq/Io/ISequence.h>
#include <Bpp/Seq/SiteTools.h>
#include <Bpp/Seq/Sequence.h>
#include <Bpp/Seq/Alphabet/DNA.h>
#include <Bpp/Phyl/TreeTemplate.h>


#include "flexible_parsimony.h"

namespace sts { namespace test { namespace flexible_parsimony {

using namespace bpp;
using namespace std;

const DNA dna;

TEST(STSFlexibleParsimony, TestAddTaxa)
{
    BasicSequence seq0("t0", "TGGAAAGTCTTTTACATTATCAATACCCTTTGGTATGCGCGAAGTTGACTAAAGTTAATAAGTAGAAAGATCTAATTTAATACCTGGAACACAGAATCTTAAAGGGACAGGGTGGTAAGAATGGGCCATACAGGCGTTCCAAGACCCTAATGATGAGCTGATTACATATTCGTCATGCAAAGTTGCCATATAGACATTTTATGGATCAAGATCGACTTAACTGATTTAGGCAAATTAGGTTCCCACGGTCGAAGGGAACGTATTTAGAACAAGGCATGGCGGAGAAACCAATAACTCAACATGAGAACCATCCGAGAGTTAAAAGTTATCCTTAAAGTAAAATAGACAAGGACACGATATGCTGTGAAAACATAATACCAGATAGTACATTGTCGGCGATAACATGAAGGAAATACACTAAAAGGACAATCCTGGATCAGGTAAGAAAAAGCAGAGCGACTTATGCTTGGAATGGCACTGAGGACCAAAGAGATAATTCATATAACCCGACTATATGTTGACAGGAGGTGGTGGAAGGGTAAAGTTGACGCTGAATTTGAAAGGTGTTTTTTGATGCTACTGTGAGACAGACTAGACATCATATGAAAATCAGCAGAGTAAGGGGCACCGAATGAATTGAGCTTGTCTAGTACAGTAATCAATATTGGAAGTTTCCGGATGATGGAGAGACGTTATATGGAAAGAAAGAATGACTAAAAGTATACTGCCGGTGATGTATGGATAATAACACTTAGTAATGCGTCACAGGTTTAGCCTTCATTGCGAATGTACAATATATTGAACGCAGTACGATGCCCGTCGGTAAGCAAGAGATAAGTTTTGCAGGCTATGAGAAGAGATGCTAAATCCCTAGGCTGAATAACCAGAGAACCGTAAAGTGAGTGAAGTACACCTTTCGGCATTATATATCAAGCCCTCTCTTGAGATTACTAGGACAGAATGGAGGGGTCGGAAGAAAAAAAATAATTATACGATTTTTAATCATTACTAAACTTGTGCCGGGTATATGACAATTTTCGAACTGCGGGACCAGCTTAATCATTATACGAACACGGCCGATCTCGAAAATAGACAGGTTCTAAACACCTTCAAAGCAGAAGTAGATGGAACCAAATTTGGCGCGCGGCAGGGGAAAAAATGGGGGATCAATGGCTAACAATGGAATAAGCTTATGGAAATTTACACGTCTCCTTTATTATCAGGATCGCTTTTTGAGAAGGTACGTGCAAACAAATCAGTAAGAAACTCCAAGTTTTCTTAATCAGGACCCCATTATGAAGCGCTGTCAACAGAACAGTTAGTAAAGTACCATAGTCGAAATTGACTTAAAAGGCTGTTAAGATCTGAAAAAATTAGAACTTCACTAGAAAAAAGGGGCATATTGGAATACTAAATTGAAAAAGCGGTGTGTGATTAATCATCTAAGAAGATGAATATAAGGTGAAGGGTCATGAGCGATTAACTTGCAGTGATAACACCGGTTAAAGCTTTCCGAAGAACCGACTAGGACGATGTGACGTACGACTGGTATTGAGAAAGAGGATAGGGCGTAAATTAGAGGAAGCAAATTAGATAGGTATCTGAGCCATACTCGATATGGAGCGGGTAGGGATGACGCTATATGACAATAGGTCGCTATAACCATCGAGTAATACGAACATGATTCTATTAATCCATGGGGATAAAGCTACAGGGTCGTCCTGAACCAAGGCGTAGTATGGTGTAAAAAAAAGTTGCAAAGGATACCACGGGTATGTCCTCCCGTAGTTCAATATTCCTTTATTTCCTGTATGTGGATTAGGGCTAGTTTTTATTTATTGAACCCGCGTTGAAGGTGTTTGAGTGTCAGAAAGGATCATCTTTGAGGTCATCAAGGTCACCAACTTCGCTAAAAATGATAGAACGTAAAATATAAAGGGCGACCCAAATTAAAACGAAAGGCACGATGAATTGTGACGTGCCTAGTGAGATGAAAAGTT", &dna);
    BasicSequence seq1("t1", "TGGAAAGTCTTTTACATTATCAATACCCTTTGGTATGCGCGAAGTTGACTAAAGTTAATAAGTAGAAAGATCTAATTTAATACCTGGAACATAGAATCTTAAAGGGACAAGGTGGTAAGAATGGGCCGTACAAGCGTTCCAAGACCCTAATAATGAGCTGATTACATATTCGTCATGCAAAATTGCCACATAGACATTTTATGGATCAAGATCGACTTAACTGATTCAGGTAAATTAGGTTCCCACGGTCGAAGGGAACGTATTTAGAACAAGGCATGGCGGAGAAACCAATAACTCAACATGAGAACCATCCGAGAGTTAAAAGTTATCCTTAAAGTAAAATAGACAAGGACACGATATGCTGTGAAAACATAATACCAGATAGTATATTGTCGGCGATAACATGAAGGAAATACACTAAGAGGACAGTCCTGGATCAGGTAAGAAAAAGCAGAATGAATTATGCTTGGAATTGCACTGAGGACCAAAGAGATAATTCATATAACCCGACTATATGTTGATAGGAGGTGGTGAAAGGGTAAAGTTGACGCTGAACTTGAAAGGTGTTTTTTGATGCTACTGTGAGACAGACTAGACATCATATGAAAATCAGCAGAGTAAGGGGCACCGAATGAATTGAGCTTGTCTAGTACAGTAATCAATATTGGAAATTTCCGGATGATGGAGAAACGTCATATGGAAAGAAAAAATGACTAAAAGTATACTGCCGGTGATGTATGGATAATAACACTTAGTAATGCGTCACAGGTTTAGCCTTCATTGCGAATGTACAATATATTGAACGCAGTACGATGCCCGTCGGTAAGCAAAAGATAAGCTTTGCAGGCTATGAGAAGAGATGCTAAATCTCTAGGCTGAATAACCAGAGAACCGTAAAGTGAATGAAGTACACCTTTCGGCATTACATATCAAGCCCTCTCTTGAGATTACTAGGACAGAATGGAGGGATCAGAAGAAAAAAAATAATTATACGATTTTTAATCATTACTAAACCTGTGCCGGGTTTATGACAATTTTCGAACTGCGGGACCAGCTTAATCATTATACGAACACGGCCGATCTCGAGAATAGACAGGTTCTAAACACCTTCAAAGCAGAAGTAGATGGAACCAAATTTGGCGCGCGGCAGGGGAAAAAATGGGGGATCAATGGCTAACAATGGAATAAGCTTATGGAAATTTATACGTCTCCTTTATTATCAGGATCGCTTCTTGAGAAGGTACGTGCAAACAAATCAGTAAGAAACTCCAAGTTTTCTTAATCAGGACCCCATTATGAAGCGCTGTCAACAGAACGGTTAGTAAAGTACCATAGTCGAAATTGACTTAAAAGGCTGTTAAGATCTGAAAAAATTAGAACTTCACTAGAAAAAAAGGGCATATTGGAATACTAAATTGAAAAAGCGGTGTGTGATTAATCATCTAAGAAGATGAATATAAGGTGAAGGGTCATGAGAGATTAACTTGCAGTGATAACACCGGTTAAAGCTTTCCGAAGAACCGACTAGGACGACGTGGCGTACGACTGGTATCGAGAAAGAGGATAGGGCGTAAATTAGAGGAAGCAAATTAGATAGGTATCTGAGCCATACTCGATGTGGAGCGGGTAGGGATGACGCTATATGACAATAGGTCGCTATAACCACCGAGTAATACGAACATGATTCTATTAATCTATGGGGATAAAGCTACGGGGTCATCCTGAACCAAAGCGTAGTATGGTGTAAAAAAAAGTTGCAAAGGATACCACGGGTATGTCCTCCCGTAGTTCAATATTCCTTTATTTCCTGTATGTGGGTTAGGGCTAGTTTTTACTTATTGAACCCGCGTTGAAGGTGTTTGAGTGTCAGAAAGGATCATCTTTGAGGTCATCAAGCTCACAAACTTCGCTAAAAATGATAGAACGTAAAATATAAAGGGCGACCCAAATTAAAACGAAAGGCACGATGAATTGTGACGTGCCTAGTAAGATGAAAAGTT", &dna);
    BasicSequence seq2("t2", "CAAAAAGTTATTCATACTATCAATATCTGCCAGTGCACGCGAAGTTAACTAAAAATCTTACACAAGAAGATTTAATTTAATGTTTGAAATGTGAGTCCCATATGGAGCGAGATAGCGGGAATAGGTCATACGGGTGATCTCAAGCTATGATAATAGACTAGCGGGAAATGCATTGTAAAAGATTGCTGTATATACGTTTTGTGAATCAAAATTAATTTAACTCATTTAAGTATATTAGATTATTATGACTGACGAAGACATATTCAGGGTAAAGAGTAACGAGAACATAAATAACTTCGCACGGAAAACATCCGAGAGCTAAAAGTTATCTTCAAAATAGAGTGGATATGGATACGATACATTGTGAGTACATAATGCTAAGTAGTACATCGTCAACAATCGCGAGAAATGGATGTACTGAAAAAATAACTCTGTATCAAGTAAAAAAAAATAAAATGAATTACACCCGAAAATGCATTATTGGTTAGAAAGAAAATTCGTGAGACCTAATAACACACTAATAGAGAGTCATAAAAAAGTAGGACTGAAATTAGATCTAAAAAATGCTTTTTGACATCGCCGTAGGAAGGATTAAACGCCATATGCGGATCAACAAAGCAACAGAAGCTAAGTAAACTAAATTTATTTAATAAAGTAGTTAATCCTGGAAGTTTTTAGATAATAAAAATACGTCACATAGGAGGAAATAATGGCCAACAATGTACTACCGGTAAGATATGGATAACAATATACAGCGATGGGTTACAGGTTTGATCCTCATCTCAGACGTACGACATATTAAATAAGATACGATGCCCGTCAATAAAGGAGAGACCGAGTCTATAGGTCATAAGGGAAGACACTGAGCCTTTAAGTTAAATGATTAAAAAACTATAAAATGAGTGAAATACACTCTTCGGCAACAAATGTTGGGCCCTTTTATGGAAATGTCGGGATGAAATAGGGAAGTCTGAAGAAAGGCAGTAATTACACGGTTTTTGGCCGTCATCAATCTTATGGTGAGTACATAACAGTTTCCAAACCGCGGATCGTGTTTGGTTATTATGGAAACACGGTCGATTCCGAAAGTAGGCAGGCCCTAAACATCTTCAGAGTAGGAATAGATGGAACCAAACTTAGCACGAGACAGAGAGAGAAGTAAGGGATCGCTGACTAACGGTGTAATGGTTCCATGGATACTCACGCGACTTTTTCATTGTTGTAATCACCTAATGAGAGGACATATGCATGTAAACTGGTAGGAAACTTTGGGTTATTTTAGTAAAGATCCCACTACGGAGTGTTGCTAGTGAAACGGTAAGAAAGATGCCGTATTAGCAGTTGGACAGAGGAATTGTTCCGGCTTATAAAGACTGGAACCTTACTAGGGAAAAGGAGCGTGTCGAGGGAACGAATTGAGAAGACCATGTGCAATCGGCCATTCAAAAAGTAATGCATAAGATGAGAAGATATGGGGGACTAAATTACAGTAATAAGAATAGCTAAGATTTCTTAAGGAACTAATTAATAAGACGTGATTTAATATGAATATCGAAAACGGGGACGGAATGTAAATTAAAGGGAGTAGATTAAGTAGATATCTTATCTATGTTAGATATAGGGCGAGCGGAAGTAACGCTAAATGATAACAGATTGTTATAATTATCGAACAATACGAATATGATTTTACTAGTCTATGGGGATAAAGCTACGAGGTTATCTTGGGATGATACGTAATGTAATACTGAAAAGAGCTGTAAGAAATATCACGGGTATGTTTGGCTATAATTCACCATTTCTCTACTTCCTTGATATAAGTTAGGGCTAGTTTATATTTTTCGAGCTTATACCGAGGGTGTGTTAGTGTTAGAAAGGATCGTCCTTAAGATCACCAAAATTACCAATCTCGTTAAAGATAATTAAGTGTAGAAGATAAGACCTGGTACAAATTAAAGCGTAGGGTGTGGCTGCTCACAATATATTCAGTAAGATAAAAACCT", &dna);
    BasicSequence seq3("t3", "CAAAAAACTATTCATACTATCGATATCTGCCAGTGCACACGAAGTTGATTAAAAATCTTACACAGGGAGGTTTCATTTAGTGCTTGGGACGTGAGTCCCATGTGGGGCGGGATAGCGGGAATAGGTCATACGGGTGATCTCAAGCTATTATAATAGACTAGCGGAAAATGCATTGTAAAAGGTTGTTATACGTACGTTTCATGAATTAAAACTAATTTAATTCATTTAAGTATATTGGATTATTATAACCGACGAAAACATGTTCAAGGTAAAGAGTAACAAGAACATGAATAACCTCGCACGAATAACATCCGAGAGCTAAAAGTTATCTTCAAAATAGAGTGGATATGGATACAATACATTGTGGGTACGTAATGTTAAGTAGTACATCGTCGACAATCGTAATAAATAGATGTACTGAAAAAGTAACTCTGTATCAAGTAAAAAGAAATAAAATGGATTACACCCGAAAATGCATTACTGGTAAGAACGAAAACTCGTGAAACTTAATAACATACTAATAGAGAATCACAGAAAAGTAGAACTGAGATTAGATCTAAAAAATGCTTTTTGACGCCACCACAGGAAGGATTAAGCGCCATGTGCGGATTGACAAAGCAATAGGTGCTGAGTGAACTAAATTCATTTAATAAAGTAGTTAATCCTGGAAGGTTTCAGATAATAAAAACACGTCACATGGGAAGGAACAATGGCCAATAATGTGCTACCGGTAAGATCTGAATAACAATGTACAGCGATAGGGTACAAGTTTGGTCTTCATCTCAGGCGTACAACATATTAAATAAGATGCAATGCCCATCAACAAAGGAGAGACTAAGTTTATAGGTCATGGGGGGAGATACCGGGCCTTTAAGCTAAATGATTAAAAAACTGTAAAATGAGTAACATATACTCTTCGGCAATAGATATTGGGCCCTTTTGTGGAAATGCCGGGGCGAGATAGGAAAGCCTGAGAAAAGGCAGTAATCGCACGGTTCTTGGCCGTCATCAATCATAAGATAAGTACATAATAGTCTTCAAACTGCGAATCGTGTTTGGTTATTATAGAAACATGGTCGATTCTGAAAGTAGGCGAGCCTTAAATGTCTTCAAGGTAGGAATAGATGAAGCCAAACTCAGCACGAGACAGGGAGGGAGGTAAGGGATAGATGATTAACGGTATAATGGTCCCATGGATGCTCACGCGACTTTTTCATTGTTGTAATCATTCAATGAGAGGACATATGCATGTAAACTAACAAGAAACTTTGGGTTATTTTAGTAAAGATCTCCCCAAGGGGTGTTGTCAGTGGAACGGTCAAAAAGGTGCCATATTAGCAATTGGATAGAGGAATTGTCCCAACTTATAAAGACTGGAACCTTGCTAGGGAAAGGAAGTGCGTCGAGGGAACGAATTGAGAAAACTATGTGTAATCGGTCATTCAAAAAGGGAAACATAAGATGAGAAGATACAGGGAACGAGATTGTGGTAGTAAAAGTAGCTAAGACTTCCTAAGGAACTAATTAATAAGACGTGATTTAACATGAATGTCGAAGACGAGGATGGTATGTAAATTAAAAGGAATAAATTAAGTGGATATCTTATCTTTGTTTAATATAGGGCAGGTGGAAGTAACGCTGAATGATAACAGATTGTTATAATTATCAAATAATACGGATATGGTTTTACTAATTTATAGAGATAAGGCCACGGGGTTATCTTGGGCAGAAACGTAATGTAGTACCGAAAGGAGCTGTAAGAAACATCAGGGGTATGTTTGACTATAATTTACCACTTTTCTACTTCATTGAGATAGGATAGGGCCAGTTTATATTTCTTGAGCTTATACCGAGGGTGTGTTAGTGTTCGAAAAGCTCACCCTCAAGATCATCGAAATTACCAGTCTCGTTAAAGGTAGTTAAGTGTGAAAGGTAAGATCTAGTCCGAATCAAAGCGTAGTGTGTGACAGATTACAGTATATTCAGTACGATAAAAACTT", &dna);
    //unique_ptr<SiteContainer> sequences = unique_ptr<VectorSiteContainer>(new VectorSiteContainer(&dna));
    SiteContainer* sequences = new VectorSiteContainer(&dna);
    sequences->addSequence(seq0, false);
    sequences->addSequence(seq1, false);
    sequences->addSequence(seq2, false);
    sequences->addSequence(seq3, false);
    SiteContainerTools::changeGapsToUnknownCharacters(*sequences);
    
    Node *root = new Node("root");
    
    Node* new_leaf0 = new Node(0, sequences->getSequence(0).getName());
    Node* new_leaf1 = new Node(1, sequences->getSequence(1).getName());
    
    root->addSon(new_leaf0);
    root->addSon(new_leaf1);
    root->getSons()[0]->setDistanceToFather(0.1);
    root->getSons()[1]->setDistanceToFather(0.2);
    
    TreeTemplate<Node>* tree = new TreeTemplate<Node>(root);
    
    vector<Node*> r = tree->getNodes();
    vector<string> names = sequences->getSequencesNames();
    int counter = sequences->getNumberOfSequences();
    for(Node* node : r){
        if(node->getNumberOfSons() == 0){
            int pos = find(names.begin(), names.end(), node->getName()) - names.begin();
            node->setId(pos);
        }
        else {
            node->setId(counter++);
        }
    }
    std::unique_ptr<SitePatterns> sp(new SitePatterns(sequences));
    sts::online::FlexibleParsimony p(*sp, dna);
    double score = p.getScore(*tree);
    ASSERT_EQ(score, 52);

    
    // Insert t2 above t1 
    Node*aNode = root->getSon(0);
    Node* father = aNode->getFather();
    double score2 = p.getScore(*tree, *aNode, sequences->getSequence(2).getName());
    ASSERT_EQ(score2, 806);
    
    Node* new_leaf2 = new Node(2, sequences->getSequence(2).getName());
    Node* temp = new Node(counter++, "leaf2dad");
    temp->addSon(new_leaf2);
    temp->addSon(aNode);
    size_t pos = father->getSonPosition(aNode);
    father->setSon(pos, temp);
    score = p.getScore(*tree);
    ASSERT_EQ(score,score2);
    
    // Insert t2 above leaf2dad 
    aNode = temp;
    score2 = p.getScore(*tree, *aNode, sequences->getSequence(3).getName());
    ASSERT_EQ(score2, 1637);
    
    Node* new_leaf3 = new Node(3, sequences->getSequence(3).getName());
    Node* temp2 = new Node(counter++, "leaf3dad");
    father = aNode->getFather();
    pos = father->getSonPosition(aNode);
    temp2->addSon(new_leaf3);
    temp2->addSon(aNode);
    father->setSon(pos, temp2);
    score = p.getScore(*tree);
    ASSERT_EQ(score,score2);
}



}}} // namespaces
