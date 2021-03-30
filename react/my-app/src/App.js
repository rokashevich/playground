import logo from './logo.svg';
import './App.css';

const Header = () => {
  return <div><a href="#s">link1</a>
    <a href="#s">link2</a>
    <a href="#s">link3</a></div>
}

const Technologies = () => {
  return <div>
    <ul>
      <li>t1</li>
      <li>t2</li>
      <li>t3</li>
    </ul>
  </div>
}

const App = () => {
  return <div>
    <Header />
    <Technologies />
  </div>

}

export default App;

