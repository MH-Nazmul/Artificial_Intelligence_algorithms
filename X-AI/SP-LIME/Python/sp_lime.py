from collections import Counter

def sp_lime(explanations,k):
    scores=Counter()
    for beta in explanations:
        for i,v in enumerate(beta):
            scores[i]+=abs(v)
    top=sorted(scores.items(),key=lambda x:-x[1])[:k]
    return [i for i,_ in top]

if __name__=="__main__":
    exps=[[0.3,-0.1,0.0],[0.2,0.4,0.1],[0.0,0.5,0.2]]
    print(sp_lime(exps,2))