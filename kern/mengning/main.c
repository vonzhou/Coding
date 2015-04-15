int g(int x){
    return x+3;
}

int f(int x){
    return g(x);
}

int main(){
    return f(8)+1;
}
