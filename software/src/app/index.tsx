import React from "react";
import { GestureHandlerRootView } from 'react-native-gesture-handler';
import { SafeAreaProvider } from "react-native-safe-area-context";
import HomeScreen from "./(tabs)/home";



function App() {
  return (
    
  <SafeAreaProvider>
    <GestureHandlerRootView>
      <HomeScreen />
    </GestureHandlerRootView>
  </SafeAreaProvider>)
}

export default App;